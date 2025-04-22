Teletubbyland is the place of the Teletubbies. It is the away in the hills. Let me introduce
you the main characters.
• Tinky Winky is the first Teletubby, as well as the largest and oldest of the group.
He is covered in purple terrycloth and has a triangular antenna on his head. He
often carries a red bag.
• Dipsy is the second Teletubby. He is green and named after his antenna, which
resembles a dipstick. Dipsy is the most stubborn of the Teletubbies, and will
occasionally refuse to go along with the group opinion.
• Laa-Laa is the third Teletubby. She is yellow and has a curly antenna. Laa-Laa
is very sweet, likes to sing and dance, and is often shown looking out for the other
Teletubbies.
• Po is the fourth Teletubby, as well as the shortest and youngest. She is red and has
an antenna shaped like a stick used for blowing soap bubbles. Her favourite toy is
a pink and blue scooter.


# ✅ Windows Service Checklist (based on your current implementation)

> Executable: `svc.exe`  
> Installer function: `create_service()`  
> Service name: `tinky`  
> Dev path: `Z:\.0_dev\tinkey_winky\svc.exe`

---

## 🧱 Core C++ Service Installer (`create_service()`)

### ✔️ What’s already implemented

- [x] Calls `OpenSCManager` with `SC_MANAGER_ALL_ACCESS`
- [x] Registers service with `CreateServiceA`
  - [x] Uses full path to `svc.exe`
  - [x] `SERVICE_DEMAND_START`
  - [x] `SERVICE_WIN32_OWN_PROCESS`
- [x] Handles `ERROR_SERVICE_EXISTS` without crashing
- [x] Reopens service with `OpenService`
- [x] Calls `StartService`
- [x] Prints error with `GetLastError()` if anything fails
- [x] Closes all service handles with `CloseServiceHandle`
- [x] Wrapped inside a clean `bool create_service()` function
- [x] Called from `main()` with simple message output

---

## 🛠️ What’s still missing or incomplete

### 🚧 Installer & Start Behavior

- [ ] Path passed to `CreateServiceA` is hardcoded  
  ➤ **TODO:** Make dynamic or configurable (e.g. from argument or config file)

- [ ] `StartService()` will fail silently if `svc.exe` is not a valid service binary  
  ➤ **TODO:** Ensure `svc.exe` contains `ServiceMain()` and properly responds to start

---

## 🧠 Inside `svc.exe`: What Must Be Implemented

> These are the **absolute requirements** to make your service run properly when `StartService()` is called.

### 🚨 Required in `svc.exe`

- [x] `main()` calls `StartServiceCtrlDispatcher()`
- [x] `ServiceMain()` is defined and registered in a `SERVICE_TABLE_ENTRY`
- [x] `RegisterServiceCtrlHandler()` is called inside `ServiceMain()`
- [x] `SetServiceStatus()` is used to set:
  - [x] `SERVICE_START_PENDING`
  - [x] `SERVICE_RUNNING`
  - [x] `SERVICE_STOP_PENDING`
  - [x] `SERVICE_STOPPED`
- [x] Main loop runs while a `g_Running` flag is `true`
- [x] `SERVICE_CONTROL_STOP` is handled and stops the loop

---

## 🧪 Service Testing & Observability

### 🧾 Testing Checklist

| Test                                | Done? | Notes                                      |
|-------------------------------------|-------|---------------------------------------------|
| `sc create tinky ...`               | ✅    | Done via `create_service()`                |
| `sc start tinky`                    | ✅    | `StartService()` works                     |
| `sc stop tinky`                     | 🔲    | Requires `ControlService` in `svc.exe`     |
| `sc delete tinky`                  | ✅    | Already included as PowerShell tip         |
| `Get-Service -Name tinky`          | ✅    | Used for live status check                 |
| `services.msc` shows "tinky"       | ✅    | Visible in GUI                             |
| Console/log output on service start| 🔲    | No logging or console in `svc.exe` yet     |

---

## 🪪 Security / Permissions

- [ ] Service currently runs under default user (likely SYSTEM)
  ➤ **TODO:** Consider using `LocalService` or specific restricted account

- [x] No interactive UI or GUI prompts inside the service (✅ good)

- [ ] Not signed with a certificate (optional for production)

---

## 📦 Deployment & Production Readiness

- [ ] Binary compiled in `Release` mode
- [ ] `/SUBSYSTEM:WINDOWS` used in linker flags (no console on service startup)
- [ ] Service path doesn't include dev path (`Z:\.0_dev\...`)
- [ ] Logging available via file or Windows Event Log
- [ ] Optional: setup script to automate install/delete

---

## 🔁 Final Feature Wishlist

| Feature                         | Implemented? |
|----------------------------------|--------------|
| Basic service creation           | ✅           |
| Basic service start              | ✅           |
| Service binary responding        | ✅           |
| Service stop (via SCM)           | 🔲           |
| Console/log file output          | 🔲           |
| Auto-restart on failure          | 🔲           |
| Arguments passed to service      | 🔲           |
| Graceful error handling/logging  | 🔲           |

---

## 💡 Quick Test Commands (for now)

```powershell
# Check if it's running
Get-Service -Name tinky

# Stop the service (when svc.exe supports stop)
sc stop tinky

# Delete the service
sc delete tinky

# Reinstall via your binary
your_installer.exe
