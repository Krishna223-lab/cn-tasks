# Task 12 — IoT Smart Home in Packet Tracer

Based on the Computer Networks lab manual, Task 12 (printed pages 86–98).

This task is mostly configured through Packet Tracer device tabs and GUIs rather than router CLI commands.

## Devices used

- WRT300N wireless home router
- PC
- RADIUS/AAA server (the manual sometimes spells it “radium”)
- IoT devices such as Fan and Door

## Addressing from the manual

| Device | IP address | Subnet mask | Default gateway |
|---|---|---|---|
| AAA/RADIUS server | `192.168.0.10` | `255.255.255.0` | `192.168.0.1` |
| WRT300N LAN | `192.168.0.1` | `255.255.255.0` | — |

The PC is configured to obtain an address using DHCP.

## 1. Configure the AAA/RADIUS server

1. Select the server → **Config** and set its display name.
2. Set IP `192.168.0.10`, mask `255.255.255.0`, gateway `192.168.0.1`.
3. Open **Services → AAA** and turn the service **On**.
4. Add user credentials for each IoT device. The manual's example uses a device username such as `fan` and password `1234`; add credentials that match the device's configuration.

## 2. Configure WRT300N

1. Select the WRT300N → **Config** and set its display name.
2. Open **GUI → Wireless** and configure the wireless network/SSID as required by your lab setup; click **Save Settings**.
3. Open the wireless **Security** section, set the security mode and credentials required by your devices, and click **Save Settings**.
4. Confirm the wireless configuration under **Config → Wireless**.

## 3. Configure the PC

1. Open PC → **Desktop → IP Configuration** (or the equivalent Config page).
2. Select **DHCP**.
3. The PC should receive an address and network settings from the wireless router.

## 4. Configure the Fan and Door

For each IoT device:

1. Select the device → **Config** and set its display name (for example, `fan` or `door`).
2. Open **Settings** and configure the remote server/AAA details according to the server and wireless-router setup.
3. Open **Config → Wireless0** and enter the matching wireless network and security settings.
4. Click **Connect** if that option is shown.

The device's wireless connection/link indicator should show successful connectivity.

## 5. Test remote control

1. On the PC, open **Desktop → Web Browser**.
2. Navigate to the server's address using the protocol configured in the lab; the manual uses `https://192.168.0.10`.
3. Register/sign in as prompted.
4. Open the device controls:
   - Fan: switch on/off or select speed.
   - Door: lock/unlock and observe the status indicator.

## Troubleshooting checklist

- Confirm the PC received an IP address using DHCP.
- Confirm the WRT300N SSID and wireless security settings match the IoT devices.
- Confirm each IoT device has the correct remote server and AAA credentials.
- Confirm the AAA service is On and user credentials have been added.
- Confirm the server IP and default gateway are correct.
- If devices do not appear in the web interface, recheck DHCP, wireless association and remote-server configuration.
