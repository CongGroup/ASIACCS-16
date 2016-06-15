# Source Code Overview

---
/src/Caravel/: cryptographic building blocks, wrapped redis api, and timer.

/src/Proxy/TProxy.cpp: Thrift-based node proxy, which responses secure get/put requests and processes secure queries for given encrypted column attributes.

/src/Client/ClientCpp.cpp: client operations inluding key-value pair encryption/decryption, generate query trapdoors.

/src/Client/SimConHash.h: implementation of consistant hashing.

/src/Client/Plaintext_cluster_latency.cpp: plaintext put/get latency evaluation.

/src/Client/Plaintext_cluster_throughput.cpp: plaintext put/get throughput evaluation.

/src/Client/Ciphertext_latency.cpp: for secure put/get latency and query latency evaluation.

/src/Client/Ciphertext_latency.cpp: for secure put/get throughput evaluation.

/src/Client/TestPT.sh: scripts that generate plaintext workloads.

/src/Client/TestCT.sh: scripts that generate ciphertext workloads.



