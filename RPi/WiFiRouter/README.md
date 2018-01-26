# Update iptable
sudo iptables-restore < iptables.rules

# Show current iptable
sudo iptables -L -v

# Show traffic from wlan0
sudo tcpdump -vv -t -i wlan0
