# 🇮🇹 (IT-version) Connect-Four (Progetto LSO a.a. 2025/2026)
6️⃣ ⚪ ⚪ ⚪ ⚪ ⚪ ⚪ ⚪ <br>
5️⃣ ⚪ ⚪ ⚪ ⚪ ⚪ ⚪ ⚪ <br>
4️⃣ ⚪ ⚪ 🔴 ⚪ ⚪ ⚪ ⚪ <br>
3️⃣ ⚪ 🔴 🟡 ⚪ ⚪ ⚪ ⚪ <br>
2️⃣ ⚪ 🟡 🔴 🟡 ⚪ ⚪ ⚪ <br>
1️⃣ 🟡 🔴 🟡 🟡 🔴 ⚪ ⚪ <br>
⠀ ⠀1️⃣ 2️⃣ 3️⃣ 4️⃣ 5️⃣ 6️⃣ 7️⃣
#

🎮 Applicazione server multi-client realizzata per il progetto di **Laboratorio di Sistemi Operativi (LSO)** <br>
📍 Università degli Studi di Napoli Federico II <br>
📚 Corso di Studio in Informatica (DIETI)


## 📁 Struttura del progetto

![Server C](https://img.shields.io/badge/Server-C-00599C?style=flat-square&logo=c) 
![Client C++](https://img.shields.io/badge/Client-C++-blue?logo=cplusplus) 
![Docker Supported](https://img.shields.io/badge/Docker-Supported-2496ED?style=flat-square&logo=docker)

Il progetto è suddiviso in due package:

* **Server**: Sviluppato in linguaggio C, implementa la logica di rete a basso livello utilizzando le system call native di GNU/Linux per la gestione dei socket. 
* **Client**: Implementato interamente in C++, sfruttando i principi OOP, gestisce la comunicazione di rete tramite le socket utilizzando le librerie standard di sistema.

## ℹ️ Funzionalità

* ✅ Comunicazione client-server tramite socket TCP
* ✅ Server dockerizzato tramite Docker
* ✅ Interfaccia utente da terminale personalizzata (CLI)
* ✅ Implementazione della logica di broadcast su socket TCP
* ✅ Sviluppo di un protocollo custom per lo scambio dati

## 🚀 Installazione ed Esecuzione

1️⃣ Clona il repository:

```bash
git clone https://github.com/RiuHz/Connect-Four.git
cd Connect-Four
```

2️⃣ Avvia il server con Docker: 
```bash
docker build -t connect-four-server .
docker run -p 1926:1926 connect-four-server
```

Se vuoi visualizzare lo stato interno del server aggiungi il flag -it:
```bash
docker run -it -p 1926:1926 connect-four-server
```

3️⃣ Avvia il client: 
```bash
cd Connect-Four/Client
make
./main
```
Vuoi avviare più client? Apri un nuovo terminale e ripeti lo step 3

# 🇬🇧 (EN-version) Connect-Four (LSO Project a.y. 2025/2026)
6️⃣ ⚪ ⚪ ⚪ ⚪ ⚪ ⚪ ⚪ <br>
5️⃣ ⚪ ⚪ ⚪ ⚪ ⚪ ⚪ ⚪ <br>
4️⃣ ⚪ ⚪ 🔴 ⚪ ⚪ ⚪ ⚪ <br>
3️⃣ ⚪ 🔴 🟡 ⚪ ⚪ ⚪ ⚪ <br>
2️⃣ ⚪ 🟡 🔴 🟡 ⚪ ⚪ ⚪ <br>
1️⃣ 🟡 🔴 🟡 🟡 🔴 ⚪ ⚪ <br>
⠀ ⠀1️⃣ 2️⃣ 3️⃣ 4️⃣ 5️⃣ 6️⃣ 7️⃣
#

🎮 Multi-client server application developed for the **Laboratory of Operating Systems (LSO)** project <br>
📍 University of Naples Federico II <br>
📚 Computer Science Degree Program (DIETI)

## 📁 Project Structure

![Server C](https://img.shields.io/badge/Server-C-00599C?style=flat-square&logo=c) 
![Client C++](https://img.shields.io/badge/Client-C++-blue?logo=cplusplus) 
![Docker Supported](https://img.shields.io/badge/Docker-Supported-2496ED?style=flat-square&logo=docker)

The project is divided into two packages:

* **Server**: Developed in C, it implements low-level network logic using native GNU/Linux system calls for socket management. 
* **Client**: Implemented entirely in C++, leveraging OOP principles, it manages network communication via sockets using standard system libraries.

## ℹ️ Features

* ✅ Client-server communication via TCP socket
* ✅ Dockerized server via Docker
* ✅ Custom terminal user interface (CLI)
* ✅ Implementation of broadcast logic over TCP sockets
* ✅ Development of a custom data exchange protocol

## 🚀 Installation and Execution

1️⃣ Clone the repository:

```bash
git clone https://github.com/RiuHz/Connect-Four.git
cd Connect-Four
```

2️⃣ Start the server with Docker:
```bash
docker build -t connect-four-server .
docker run -p 1926:1926 connect-four-server
```

If you want to view the internal status of the server, add the -it flag:
```bash
docker run -it -p 1926:1926 connect-four-server
```

3️⃣ Start the client:
```bash
cd Connect-Four/Client
make
./main
```
Want to launch multiple clients? Open a new terminal and repeat step 3.
