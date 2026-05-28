# sixbitd Init Scripts and Service Configuration

## Overview
Sample scripts and configuration files for systemd, OpenRC, and Upstart are available in the `contrib/init` directory:

- `sixbitd.service` – systemd service unit  
- `sixbitd.openrc` – OpenRC init script  
- `sixbitd.openrcconf` – OpenRC configuration file  
- `sixbitd.conf` – Upstart configuration  
- `sixbitd.init` – SysV init script (CentOS)  

---

## Service User
Create a dedicated user and group:

```
sudo useradd -r -m -d /var/lib/sixbitd -s /usr/sbin/nologin sixbit
```

macOS uses the current user by default.

---

## Configuration

### RPC Authentication
By default, sixbitd uses cookie-based authentication.

Optional:
```
rpcauth=<USERNAME>:<SALT>$<HASH>
```

### Cookie Settings
- Default: data directory  
- Override: `-rpccookiefile`  
- Permissions: owner-only (umask 0077)  

### Path Behavior
- `conf`, `pid`, `wallet` support relative paths  
- `wallet` must be relative  

---

## Linux Paths

- Binary: `/usr/bin/sixbitd`  
- Config: `/etc/sixbit/sixbit.conf`  
- Data: `/var/lib/sixbitd`  
- PID: `/run/sixbitd/sixbitd.pid`  

Ensure directories are owned by `sixbit:sixbit`.

---

## macOS Paths

- Binary: `/usr/local/bin/sixbitd`  
- Config/Data: `~/Library/Application Support/sixbit`  

---

## systemd Installation

```
sudo cp contrib/init/sixbitd.service /lib/systemd/system/
sudo systemctl daemon-reload
sudo systemctl start sixbitd
sudo systemctl enable sixbitd
```

---

## OpenRC Installation

```
sudo cp contrib/init/sixbitd.openrc /etc/init.d/sixbitd
sudo chmod +x /etc/init.d/sixbitd
/etc/init.d/sixbitd start
rc-update add sixbitd
```

---

## Upstart Installation (Legacy)

```
sudo cp contrib/init/sixbitd.conf /etc/init/
service sixbitd start
```

---

## CentOS (SysV)

```
sudo cp contrib/init/sixbitd.init /etc/init.d/sixbitd
service sixbitd start
```

Config file:
```
/etc/sysconfig/sixbitd
```

---

## macOS LaunchAgent

```
cp org.sixbit.sixbitd.plist ~/Library/LaunchAgents/
launchctl load ~/Library/LaunchAgents/org.sixbit.sixbitd.plist
```

---

## Auto-Respawn
Enabled by default for systemd and Upstart.

---

## Notes
- Init scripts override `datadir` settings in config
- Use init-specific variables to override behavior
- Restrict file permissions for security

---

## License
MIT License
