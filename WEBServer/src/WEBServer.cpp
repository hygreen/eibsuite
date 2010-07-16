#include "WEBServer.h"
#include "StatsDB.h"
#include "cli.h"

CWEBServer CWEBServer::_instance;

CWEBServer::CWEBServer() : 
CGenericServer(EIB_TYPE_WEB_SERVER),
CSingletonProcess(WEB_SERVER_PROCESS_NAME),
_dispatcher(NULL),
_collector(NULL),
_conf_file(CURRENT_CONF_FOLDER + WEB_CONF_FILE_NAME)
{
	_dispatcher = new CDispatcher();
	_collector = new CWebCollector();
}

CWEBServer::~CWEBServer()
{
}

void CWEBServer::Run(void *arg)
{
	CGenericServer::Init(&_log);
	bool established = false;
	if(_conf.GetAutoDiscoverEibServer())
	{
		_log.Log(LOG_LEVEL_INFO,"Searching EIB Server on local network...");
		established = this->OpenConnection(_conf.GetNetworkName().GetBuffer(),
											_conf.GetInitialKey().GetBuffer(),
											Socket::LocalAddress(_conf.GetListenInterface()).GetBuffer(),
											_conf.GetName().GetBuffer(),
											_conf.GetPassword().GetBuffer());
	}
	else
	{
		established = this->OpenConnection(_conf.GetNetworkName().GetBuffer(),
											_conf.GetEibIPAddress(),
											_conf.GetEibPort(),
											_conf.GetInitialKey().GetBuffer(),
											Socket::LocalAddress(_conf.GetListenInterface()).GetBuffer(),
											_conf.GetName().GetBuffer(),
											_conf.GetPassword().GetBuffer());
	}

	if (!established)
	{
		_log.Log(LOG_LEVEL_INFO,"\nCannot establish connection with EIB Server!\n");
		return;
	}
	else{
		_log.Log(LOG_LEVEL_INFO,"\nEIB Server Connection established.\n");
	}

	_collector->start();
	_dispatcher->start();
}

void CWEBServer::Close()
{
	_log.Log(LOG_LEVEL_INFO,"Saving Configuration file...");
	_conf.Save(CURRENT_CONF_FOLDER + WEB_CONF_FILE_NAME);

	//close the heart beat thread
	_log.Log(LOG_LEVEL_INFO,"Closing Generic Server module...");
	_collector->Close();
	CGenericServer::Close();
	
	//close the dispatcher
	_log.Log(LOG_LEVEL_INFO,"Closing Dispatcher...");
	_dispatcher->Close();

	CTime t;
	//indicate user
	_log.Log(LOG_LEVEL_INFO,"WEB Server closed on %s",t.Format().GetBuffer());
}

bool CWEBServer::Init()
{
	bool res = true;

	START_TRY
		_log.Init(CURRENT_LOGS_FOLDER + DEFAULT_LOG_FILE_NAME);
		_log.Log(LOG_LEVEL_INFO,"Initializing Log manager...Successful");
	END_TRY_START_CATCH_ANY
		cerr << "Initializing Log manager...Failed." << endl;
		return false;
	END_CATCH
		
	START_TRY
		//load configuration from file
		_conf.Load(_conf_file);
		_log.Log(LOG_LEVEL_INFO,"Reading Configuration file...Successful.");
	END_TRY_START_CATCH(e)
		_log.Log(LOG_LEVEL_ERROR,"Reading Configuration file...Failed. Reason: %s",e.what());
		res = false;
	END_CATCH
	
	START_TRY	
		_users.Init(CURRENT_CONF_FOLDER + DEFAULT_USERS_DB_FILE_NAME);
		_users.Load();
		if(_users.GetNumOfUsers() == 0)	{
			throw CEIBException(ConfigFileError,"No Users defined in \"%s\".",DEFAULT_USERS_DB_FILE_NAME);
		}
		_log.Log(LOG_LEVEL_INFO,"Initializing Users DB...Successful.");
	END_TRY_START_CATCH(e)
		_log.Log(LOG_LEVEL_ERROR,"Initializing Users DB...Failed. Reason: %s",e.what());
		res = false;
	END_CATCH
	
	START_TRY
		_dispatcher->Init();
		_log.Log(LOG_LEVEL_INFO,"Initializing WEB Interface...Successful.");
	END_TRY_START_CATCH(e)
		_log.Log(LOG_LEVEL_ERROR,"Initializing WEB Interface...Failed. Reason: %s",e.what());
		res = false;
	END_CATCH
	
	_domain = _dispatcher->GetServerAddress();
	if(_dispatcher->GetServerPort() != DEFAULT_WEB_PORT){
		_domain += ':';
		_domain += _dispatcher->GetServerPort();
	}
	_log.Log(LOG_LEVEL_INFO,"WEB Server Address is http://%s/",_domain.GetBuffer());

	CTime t;
	CString time_str = t.Format();
	//indicate user
	_log.Log(LOG_LEVEL_INFO,"WEB Server started on %s\n",time_str.GetBuffer());
	
	return res;
}

CWEBServer& CWEBServer::GetInstance()
{
	return _instance;
}

void CWEBServer::InteractiveConf()
{
	START_TRY
		_conf.Load(_conf_file);
	END_TRY_START_CATCH_ANY
		_conf.Init();
	END_CATCH

	LOG_SCREEN("************************************\n");
	LOG_SCREEN("WEB Server Interactive configuration:\n");
	LOG_SCREEN("************************************\n");

	CString sval;
	int ival;
	bool bval;
	if(ConsoleCLI::GetCString("Initial Encryption/Decryption key?",sval, _conf.GetInitialKey())){
		_conf.SetInitialKey(sval);
	}
	if(ConsoleCLI::Getbool("Auto detect EIBServer on local network?",bval,_conf.GetAutoDiscoverEibServer())){
		_conf.SetAutoDiscoverEibServer(bval);
		if(!bval){
			if(ConsoleCLI::GetCString("EIBServer IP Address?",sval,_conf.GetEibIPAddress())){
				_conf.SetEibIPAddress(sval);
			}
			if(ConsoleCLI::Getint("EIB Server port?",ival, _conf.GetEibPort())){
				_conf.SetEibPort(ival);
			}
		}
	}
	
	if(ConsoleCLI::Getint("WEB Server listening port?",ival, _conf.GetWEBServerPort())){
		_conf.SetWEBServerPort(ival);
	}
	if(ConsoleCLI::GetCString("WEB Server user name (used to connect to EIB Server)?",sval, _conf.GetName())){
		_conf.SetName(sval);
	}
	if(ConsoleCLI::GetCString("WEB Server password (used to connect to EIB Server)?",sval, _conf.GetPassword())){
		_conf.SetPassword(sval);
	}

	map<CString,CString> map2;
	
#ifdef WIN32
	if(CUtils::EnumNics(map2) && ConsoleCLI::GetStrOption("Choose Interface to listen for web requests (Browser)", map2, sval, CString(_conf.GetListenInterface()))){
		_conf.SetListenInterface(sval.ToInt());
	}
#else
	if(CUtils::EnumNics(map2) && ConsoleCLI::GetStrOption("Choose Interface to listen for web requests (Browser)", map2, sval, _conf.GetListenInterface())){
		_conf.SetListenInterface(sval);
	}
#endif

	_conf.Save(_conf_file);
	LOG_SCREEN("Running WEB Server with updated configuration...\n");
}