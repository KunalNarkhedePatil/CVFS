# Customized Virtual File System(CVFS) - C++ Project

## 📌 Introduction
The **Customized Virtual File System(CVFS)** is a powerful and efficient file management system built in C++. It utilizes **Dynamic Link Libraries (DLLs)** to execute essential file operations such as **creating, opening, reading, writing, renaming, and deleting files** via a **command-line interface**. This project mimics traditional file handling systems while offering modularity, efficiency, and ease of use.

Designed with a **modular approach**, the VFS encapsulates core functionalities within DLLs to improve **code reuse** and **memory management**. By implementing **key system calls** (`Open`, `Close`, `Read`, `Write`, `Lseek`, `Create`, `RM`), the VFS ensures seamless file operations similar to a native file system. 

To enhance **data organization and management**, linked lists and arrays are used, ensuring optimized storage and performance.

## 🔹 Features
- **Core File Operations**: Create, Open, Read, Write, Rename, Delete
- **System Calls Implementation**: Open, Close, Read, Write, Lseek, Create, RM
- **Efficient Data Management**: Uses linked lists and arrays for optimized performance
- **Modular Architecture**: Core functionalities encapsulated within DLLs for reusability
- **Command-Line Interface**: Allows users to interact with files effortlessly
- **Performance Optimization**: Well-structured data handling improves speed and efficiency

## 🚀 How It Works
### ✅ Initialization:
- The system initializes by loading necessary **DLL components**.
- Establishes **memory structures** using linked lists and arrays.

### ✅ File Management:
- **Create a new file** using the `Create` system call.
- **Open an existing file** using `Open`, with appropriate access permissions.
- **Read or write** using `Read` and `Write`, ensuring proper data handling.
- **Rename a file** efficiently using `Rename`.
- **Delete unnecessary files** via `RM` for cleanup.
- **Manage file pointer** using `Lseek` for data retrieval modifications.

👨‍💻 **LinkedIn:** [Project Link](https://l1nk.dev/1hRlF)

### ✅ Command-Line Interaction:
The user interacts with files through a simple command-based system:
```bash
VFS> create myfile.txt
VFS> open myfile.txt
VFS> write myfile.txt "Hello, World!"
VFS> read myfile.txt
VFS> rename myfile.txt newfile.txt
VFS> rm newfile.txt
