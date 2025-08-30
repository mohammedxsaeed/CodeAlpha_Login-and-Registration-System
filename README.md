# 🔐 User Authentication System (C++)

### Author: Mohammed Saeed

---

## 📌 Overview
This project is a **User Authentication System** implemented in **C++**.  
It allows users to:
- **Register** a new account.
- **Login** using their credentials.
- **Delete** an existing account.

All user data is stored in a text file (`database.txt`) in a **table format**, where **passwords are securely hashed** before saving.

---

## ⚙️ Features
- 📂 Stores credentials persistently in `database.txt`.
- 🔑 Passwords are hashed using a **custom hashing function** for extra security.
- 🧾 Data is stored in a **clean table format** (Username | Hashed Password).
- ✅ Supports:
  - User Registration
  - User Login
  - Account Deletion (with confirmation)
- 🚫 Prevents duplicate usernames.
- 🔄 Interactive menu-driven console program.

