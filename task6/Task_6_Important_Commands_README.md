# Task 6 — Important Computer Networks Commands

Quick revision sheet for Task 6: basic Cisco switch configuration and network diagnostic commands.

## 1. Switch configuration commands

Enter these in the switch CLI in order where appropriate:

```text
enable
configure terminal
hostname S1
no ip domain-lookup
enable secret class
service password-encryption
banner motd #Authorized access only!#
line console 0
password cisco
login
exit
line vty 0 4
password cisco
login
exit
end
copy running-config startup-config
```

Replace the example hostname and passwords with the values required by your lab.

| Command | Purpose |
|---|---|
| `enable` | Enters privileged EXEC mode (`Switch#`). |
| `configure terminal` | Enters global configuration mode. |
| `hostname S1` | Changes the switch's hostname. |
| `no ip domain-lookup` | Stops the switch from trying DNS lookup when a command is mistyped. |
| `enable secret class` | Sets the encrypted password for privileged EXEC mode. |
| `service password-encryption` | Encrypts eligible plaintext passwords in the configuration. |
| `banner motd #...#` | Configures a message-of-the-day login banner. |
| `line console 0` | Enters console-line configuration mode. |
| `line vty 0 4` | Enters configuration mode for VTY lines 0–4 (remote CLI access). |
| `password cisco` | Sets a line password. |
| `login` | Requires the configured line password when accessing that line. |
| `end` | Returns to privileged EXEC mode. |
| `copy running-config startup-config` | Saves the current configuration so it remains after a reboot. |

## 2. Verification commands

```text
show running-config
show startup-config
show version
show mac address-table
```

- `show running-config` — shows the active configuration in RAM.
- `show startup-config` — shows the saved configuration.
- `show version` — shows device/software information and uptime.
- `show mac address-table` — shows MAC addresses learned by the switch.

## 3. Network diagnostic commands

Run these from a PC's Command Prompt in Packet Tracer, or from the relevant terminal on your operating system:

```text
ping 192.168.1.2
tracert 192.168.1.2
traceroute 192.168.1.2
nslookup example.com
ipconfig
arp -a
```

| Command | Purpose |
|---|---|
| `ping <IP>` | Tests reachability using ICMP echo requests and replies. |
| `tracert <IP>` | Traces the route on Windows. |
| `traceroute <IP>` | Traces the route on macOS/Linux and many network devices. |
| `nslookup <domain>` | Queries DNS to resolve a domain name. |
| `ipconfig` | Shows PC IP configuration in Windows/Packet Tracer. |
| `arp -a` | Shows the local ARP cache (IP-to-MAC mappings). |

Use the command appropriate to your environment: `tracert` is commonly used on Windows; `traceroute` is commonly used on macOS/Linux. In Packet Tracer PC Command Prompt, supported commands can differ from your real computer's terminal.

## 4. Common configuration modes

- `Switch>` — user EXEC mode.
- `Switch#` — privileged EXEC mode.
- `Switch(config)#` — global configuration mode.
- `Switch(config-line)#` — console or VTY line configuration mode.

Useful navigation:
```text
enable
configure terminal
line console 0
exit
end
```

**Remember:** `exit` moves back one level; `end` returns directly to privileged EXEC mode.
