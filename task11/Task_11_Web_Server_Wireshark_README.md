# Task 11 — Web Server, DNS, Wireshark and NIC Information

Based on the Computer Networks lab manual, Task 11 (printed pages 76–85).

## Part A — Web server with DNS in Packet Tracer

### IP addressing from the manual

| Device | IP address | DNS server |
|---|---|---|
| PC0 | `192.168.1.3` | `192.168.1.1` |
| Web Server | `192.168.1.2` | `192.168.1.1` |
| DNS Server | `192.168.1.1` | `192.168.1.1` |

Set suitable subnet masks (the manual's example network is `192.168.1.0/24`) and configure the PCs' gateway if a router is present.

### DNS server setup

1. Click the DNS Server → **Services → DNS**.
2. Turn DNS service **On**.
3. Add an A record:
   - Name: `example.com`
   - Address: `192.168.1.2`
4. Click **Add**.

### Web server setup

1. Click the Web Server → **Services → HTTP**.
2. Turn **HTTP On** (and HTTPS On if needed).
3. Edit `index.html` if you want a custom page. Example:

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <title>Welcome to example</title>
</head>
<body>
  <h1>Welcome to example</h1>
  <p>The best networking blog.</p>
</body>
</html>
```

### Test from PC0

Open **Desktop → Web Browser** and enter:

```text
http://example.com
```

You can also test DNS and connectivity from **Desktop → Command Prompt**:

```text
ping 192.168.1.2
ping example.com
nslookup example.com
ipconfig
```

## Part B — Capture traffic using Wireshark

1. Open Wireshark and select the active network interface.
2. Start capturing.
3. Generate traffic from a command prompt, for example:

```text
ping google.com
ping cisco.com
```

4. Stop the capture.
5. Select an ICMP Echo Request packet and inspect its source/destination IPs and protocol layers.

Useful Wireshark display filters:

```text
icmp
dns
tcp
udp
arp
```

These are display filters typed in Wireshark's filter bar, not terminal commands.

## Part C — Wired/wireless NIC information

On Windows, open Command Prompt:

```text
ipconfig /all
```

Record the adapter description, IPv4 address, physical (MAC) address, subnet mask, default gateway and DNS servers. Compare the result with the adapter details in Network Connections / adapter Properties.

### Quick meanings

- `ping`: tests reachability with ICMP.
- `nslookup`: queries DNS name resolution.
- `ipconfig /all`: displays detailed interface configuration and MAC address.
- Wireshark packet list: captured frames; packet details: decoded protocol layers; packet bytes: raw data.
