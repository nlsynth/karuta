import os

HOME = os.getenv("HOME")
SD_DIR = HOME + "/.local/share/systemd/user/"
PWD = os.getcwd()

ofh = open("karuta@.service", "w")

ofh.write("""
[Unit]
Description = Karuta

[Service]
ExecStart = /usr/bin/python3 """ + PWD + """/wrapper.py
Type = simple
# ProtectSystem = strict
# PrivateNetwork = true
StandardInput=socket
StandardOutput=socket
Environment=KARUTA_BIN=""" + PWD + """/karuta-bin
Environment=KARUTA_DIR=""" + PWD + """

""")

ofh.close()

ofh = open("karuta.socket", "w")
ofh.write("""
[Unit]
Description = Karuta server socket

[Socket]
ListenStream = 127.0.0.1:9090
Accept=yes

[Install]
WantedBy=sockets.target
""")
ofh.close()

os.system("cp karuta@.service " + SD_DIR)
os.system("cp karuta.socket " + SD_DIR)

# systemctl --user enable karuta.socket
# systemctl --user start karuta.socket

# systemctl --user disable karuta.socket
