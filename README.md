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


# ✅ Windows Service Development Checklist

## 🧱 CORE IMPLEMENTATION

- [x] `ServiceMain` function defined  
- [x] `ServiceCtrlHandler` registered with `RegisterServiceCtrlHandler()`  
- [x] `StartServiceCtrlDispatcher()` called in `main()`  
- [x] `SetServiceStatus()` called with:
  - [x] `SERVICE_START_PENDING`
  - [x] `SERVICE_RUNNING`
  - [x] `SERVICE_STOP_PENDING`
  - [x] `SERVICE_STOPPED`  
- [x] Main service loop that runs while `g_Running == true`  
- [x] Clean exit when `SERVICE_CONTROL_STOP` is received  

---

## 🔌 SERVICE BEHAVIOR & INTERACTIONS

- [ ] Add logging (stdout or Event Viewer)
- [ ] Add `SERVICE_ACCEPT_PAUSE_CONTINUE` support (optional)
- [ ] (Optional) Implement `SERVICE_CONTROL_INTERROGATE`
- [ ] (Optional) Add argument parsing from `StartService(..., args)` if needed

---

## ⚙️ SERVICE CREATION & CONTROL

- [x] `CreateServiceA()` used to register the service from a tool or program
- [x] `OpenService()` + `StartService()` tested successfully
- [x] `sc stop tinky` works correctly (service exits cleanly)
- [ ] `sc delete tinky` tested and works
- [x] Error 1056 handled (service already running)
- [ ] Error handling for `StartServiceCtrlDispatcher` and other critical calls

---

## 🧪 TESTING & VALIDATION

- [x] Service appears in `services.msc`
- [x] `Get-Service tinky` shows status correctly
- [ ] Service can survive reboot (`SERVICE_AUTO_START`) if needed
- [ ] Behavior validated when run as SYSTEM / LocalService
- [ ] Service tested on a clean machine or VM

---

## 📦 PACKAGING & DEPLOYMENT

- [ ] Service binary compiled in **Release** mode
- [ ] No console window opens when run (`/SUBSYSTEM:WINDOWS` in linker flags)
- [ ] Installer or script to create the service (`sc create`, or your tool)
- [ ] Proper `binPath=` in CreateService (uses full path)
- [ ] (Optional) Signed binary (if deploying on production environments)

---

## 🔒 SECURITY & PERMISSIONS

- [ ] Uses least privilege account (`LocalService`, `NetworkService`)
- [ ] Does **not** interact with desktop (no GUI calls or MessageBox)
- [ ] Handles access rights properly (`OpenService(..., SERVICE_* flags)`)

---

## 🎁 BONUS / NICE TO HAVE

- [ ] Event Viewer logging (`ReportEvent`)
- [ ] Log file output with timestamps
- [ ] IPC or socket server (e.g. to receive commands)
- [ ] Automatic restart on failure (`sc failure` config)
- [ ] Unit tests (for any logic inside service loop)
