## Linux Kernel Module Project (LKM)

## 📌 Overview

This repository contains a step-by-step implementation of **Linux Kernel Modules (LKM)** with a focus on building a **production-level character device driver**.

The goal of this project is not just to demonstrate basic kernel module usage, but to deeply understand:

* Kernel-space vs User-space boundaries
* Memory management in kernel space
* Synchronization and concurrency control
* Device driver architecture
* Stable and safe user-kernel interfaces

---

## 🎯 Goals

* Build a fully functional **character device driver**
* Implement **user ↔ kernel communication**

  * `read`
  * `write`
  * `ioctl`
* Apply proper **synchronization mechanisms**
* Design a **robust and maintainable kernel interface**
* Handle **error cases and edge conditions safely**

---

## 🛠 Development Environment

* **Host**: macOS + Asahi Linux
* **OS**: Fedora Asahi Remix 43
* **Architecture**: ARM64 (`aarch64`)
* **Kernel**: Fedora kernel (16K page variant possible)
* **Build System**: Linux Kbuild (out-of-tree module)

> ⚠️ Note
> This project is developed and tested on ARM64.
> However, the core driver logic is written to be **architecture-agnostic** and can be ported to x86_64 environments with matching kernel headers.

---

## 📂 Project Structure

```
lkm-project/
├── 01_hello/          # Basic kernel module (init/exit, printk)
├── 02_params/         # Module parameters (runtime configuration)
├── 03_memory/         # Kernel memory management (kmalloc/kfree)
├── 04_chardev/        # Character device driver (core project)
├── scripts/           # Utility scripts (build/run helpers)
└── README.md
```

---

## 🚀 Getting Started

### 1. Install Dependencies

```bash
sudo dnf install -y \
    gcc make git \
    elfutils-libelf-devel \
    kernel-16k-devel
```

---

### 2. Build a Module

```bash
cd 01_hello
make
```

---

### 3. Load / Unload Module

```bash
sudo insmod hello.ko
sudo rmmod hello
```

---

### 4. Check Kernel Logs

```bash
dmesg | tail -n 20
```

or

```bash
sudo journalctl -k -n 50
```

---

## 🔁 Development Workflow

Typical workflow when developing kernel modules:

```text
Edit code → Build (make) → Load (insmod) → Check logs (dmesg) → Debug → Repeat
```

For convenience:

```bash
./run.sh
```

---

## 🧠 Key Learning Areas

### 1. Kernel Module Lifecycle

* `module_init`
* `module_exit`
* Resource allocation and cleanup

### 2. Memory Management

* `kmalloc` / `kfree`
* Kernel vs user memory constraints
* Avoiding memory leaks and use-after-free

### 3. User ↔ Kernel Communication

* `copy_to_user`
* `copy_from_user`
* Designing safe interfaces

### 4. Character Device Driver

* `file_operations`
* `open`, `read`, `write`, `release`
* Device registration (`cdev`)

### 5. Synchronization

* `mutex`
* `spinlock`
* Race condition prevention

---

## ⚠️ Design Philosophy

This project focuses on **understanding the "why" behind each implementation**, not just making it work.

Key principles:

* Explicit resource ownership
* Clear separation of responsibilities
* Defensive programming (fail early, fail safely)
* Avoiding undefined behavior in kernel space
* Writing code that is maintainable and debuggable

---

## 🧪 Testing Strategy

* Manual testing via `insmod` / `rmmod`
* Kernel log verification (`dmesg`)
* User-space test programs (for char device)
* Stress testing for concurrency issues (later stages)

---

## 📈 Future Extensions

* Blocking I/O with wait queues
* `poll` / `select` / `epoll` support
* Ring buffer implementation
* Performance optimization
* Multi-threaded user-space test tool

---

## 📚 References

* Linux Kernel Documentation
* LDD3 (Linux Device Drivers, 3rd Edition)
* Kernel source code

---

## 👨‍💻 Author

**Park Jinhyeok**

---

## 💬 Notes

This project is part of a deeper study into **Linux kernel development and low-level system programming**, aiming to reach a level suitable for **kernel / embedded software engineering roles**.
