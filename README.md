# Keylogger-Using-CPP

Advanced keylogger developed using C++ for penetration testing, compatible with Windows 7, 8, 8.1, and 10. This project was developed after completing the **Udemy - Advanced Keylogger** course. 

The project includes a decryption program that accepts an encrypted log file and translates it into a human-readable format.

If you want to take the course, you can find it [here](https://www.udemy.com/how-to-create-an-advanced-keylogger-from-scratch-for-windows).

---

## Features
- Well-commented source code for easy understanding.
- Low resource usage with no visible windows when running.
- Asynchronous execution of processes.
- Captures all keystrokes using system hooks.
- Automatically logs the time and date when a log file is generated.
- Uses Base64 encryption with modifications and multiple encoding layers.
- Generates and invokes a PowerShell script to send encrypted logs via email.
- Various customization options:
  - Process name
  - Time interval for log generation
  - Key formatting options
  - Excluding specific keys

---

## Important Information
- Log files are stored in: `C:\Users\($User)\AppData\Roaming\Microsoft\CLR`
- App log files are generated in this location for debugging purposes.
- Running multiple instances of the keylogger may cause issues.
- The default process name in Task Manager is `Keylogger.exe`.

---

## Prerequisites
- **Any C++-compatible IDE**.
- **C++11** standard enabled.
- If using **GCC**, ensure the `-mwindows` flag is checked.

---

## Installing
1. Clone the repository:
   ```bash
   git clone https://github.com/The-Red-Serpent/Keylogger-Using-CPP.git
   ```
2. Open the main source file (`main.cpp`) in your C++ IDE.
3. Compile and run the program.

---

## Decrypting the Log Files
1. Navigate to the decryption program folder:
   ```bash
   Keylogger-Using-CPP/Decryption Program/
   ```
2. Compile the decryption program.
3. Run the decryption tool:
   ```bash
   ./Decryption "inputfile.log" "outputfile.log"
   ```

---

## Deploying the Keylogger
1. Compile the `main.cpp` file using your C++ compiler.
2. Locate the generated executable file.
3. Run the executable.

---

## License
This project is licensed under the **MIT License**. See the `LICENSE.md` file for details.

---

## Disclaimer
This software is strictly for **educational and penetration testing** purposes. **Unauthorized usage on systems you do not own is illegal and punishable by law. The responsibility is solely on the user.**

---

## Acknowledgments
Special thanks to **Ermin Kreponic** for his excellent Udemy course on keylogger development. Check out his [Udemy profile](https://www.udemy.com/user/erminkreponic/) for more courses.

---

