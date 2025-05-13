# pipex

## 📚 About the Project

**pipex** is a Unix-based project from the 42 coding school curriculum that focuses on understanding pipes, process forking, and file descriptors in C. The objective is to replicate shell behavior by executing commands connected via pipes, with input and output redirection.

This project provides a deeper understanding of how a shell handles command execution, inter-process communication, and system-level I/O.

---

## 🧩 Project Objective

Create a program that mimics the shell pipeline behavior:

```bash
< infile cmd1 | cmd2 > outfile
```

Your program must:

- Open an input file
- Execute `cmd1`, redirecting its output to the input of `cmd2`
- Execute `cmd2`, redirecting its output to the output file
- Handle file and command errors gracefully

---

## 🛠️ How to Use

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/pipex.git
   cd pipex
   ```

2. Compile the project:
   ```bash
   make
   ```

3. Run the program:
   ```bash
   ./pipex infile "cmd1" "cmd2" outfile
   ```

   Example:
   ```bash
   ./pipex input.txt "grep hello" "wc -l" output.txt
   ```

   Equivalent to:
   ```bash
   < input.txt grep hello | wc -l > output.txt
   ```

---

## 🔧 Bonus Features

✅ **Multiple Commands** – Support for an arbitrary number of commands, enabling full pipeline chains:

```bash
./pipex infile "cmd1" "cmd2" "cmd3" "cmd4" outfile
```

Equivalent to:

```bash
< infile cmd1 | cmd2 | cmd3 | cmd4 > outfile
```

✅ **here_doc Mode** – Simulates shell `here document` behavior:

```bash
./pipex here_doc LIMITER "cmd1" "cmd2" outfile
```

Equivalent to:

```bash
<< LIMITER cmd1 | cmd2 >> outfile
```

- Appends to the `outfile` instead of truncating it
- Takes input from standard input until the `LIMITER` is encountered

---

## 🧠 Skills Demonstrated

- Inter-process communication using pipes  
- File descriptor manipulation and redirection  
- Process creation with `fork` and `execve`  
- Dynamic pipeline building  
- Handling `here_doc` input streams  
- PATH resolution and environment variable management  
- Error handling and resource cleanup  
- Implementation of shell-like behavior in C

---

## 📁 Project Status

✅ Completed – includes all mandatory and bonus features, fully functional and tested.

---

## 📌 Notes

- Avoids use of `system()` or other shell wrappers — all behavior implemented manually
- Includes support for relative and absolute paths
- Compliant with 42’s strict coding standards and project specifications

---

## 📫 Contact

Feel free to reach out via [GitHub](https://github.com/Nicolike20) if you have any questions or want to connect.

[![forthebadge](https://forthebadge.com/images/featured/featured-built-with-love.svg)](https://forthebadge.com)
