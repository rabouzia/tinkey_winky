#include "tinkey_winky.hpp"
#define SERVICE_NAME "tinky"

/*
	for test:
	Get-Service -Name tinky
	for delete:
	Get-Service -Name "tinky" | ForEach-Object { sc.exe delete $_.Name }
*/

SERVICE_STATUS g_ServiceStatus = {};
SERVICE_STATUS_HANDLE g_StatusHandle = nullptr;
bool g_Running = true;

bool create_service()
{

	SC_HANDLE hSCManager = OpenSCManager(nullptr, nullptr, SC_MANAGER_ALL_ACCESS);
	if (!hSCManager)
	{
		std::cerr << "OpenSCManager failed: " << GetLastError() << std::endl;
		return false;
	}
	std::cout << "OpenSCManager succeeded." << std::endl;

	SC_HANDLE hService = CreateServiceA(
		hSCManager,
		SERVICE_NAME,
		"tinky",
		SERVICE_ALL_ACCESS,
		SERVICE_WIN32_OWN_PROCESS,
		SERVICE_DEMAND_START,
		SERVICE_ERROR_NORMAL,
		"Z:\\.0_dev\\tinkey_winky\\svc.exe",
		nullptr, nullptr, nullptr, nullptr, nullptr);

	if (!hService)
	{
		DWORD err = GetLastError();
		if (err == ERROR_SERVICE_EXISTS)
			std::cout << "Service already exists." << std::endl;
		else
		{
			std::cerr << "CreateService failed: " << err << std::endl;
			CloseServiceHandle(hSCManager);
			return false;
		}
	}
	else
		CloseServiceHandle(hService); // Close if newly created, will reopen below
	hService = OpenService(hSCManager, SERVICE_NAME, SERVICE_START | SERVICE_QUERY_STATUS);
	if (!hService)
	{
		std::cerr << "OpenService failed: " << GetLastError() << std::endl;
		CloseServiceHandle(hSCManager);
		return false;
	}
	if (!StartService(hService, 0, nullptr))
		std::cerr << "StartService failed: " << GetLastError() << std::endl;
	else
		std::cout << "Service Started" << std::endl;
	
	
		CloseServiceHandle(hService);
	CloseServiceHandle(hSCManager);
	return true;
}


int main()
{
	if (!create_service())
		return 0;
	// if (!OpenService())
	std::cout << "\nTo check the service, run in terminal:\n  sc query MyTestService\n";
	std::cout << "To delete it:\n  sc delete MyTestService\n";

	return 0;
}