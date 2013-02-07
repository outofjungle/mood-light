APP_NAME = mood-light
PYSERIAL_URL = http://pypi.python.org/packages/source/p/pyserial/pyserial-2.6.tar.gz
PYSERIAL_DIR = $(subst .tar.gz,,$(notdir $(PYSERIAL_URL)))

.PHONY: install-pyserial

install-pyserial: 
	curl $(PYSERIAL_URL) | tar -xz; \
	cd $(PYSERIAL_DIR); sudo python setup.py install; \

create-log-dir:
	sudo mkdir /var/log/$(APP_NAME); \
	sudo chown pi:pi /var/log/$(APP_NAME); \

install-service:
	sudo mkdir -m0755 -p /service/sync2serial_daemon; \
	sudo cp bin/sync2serial /usr/bin; \
	sudo cp service/run /service/sync2serial_daemon/run; \
	sudo cp conf/sync2serial.conf /etc; \
	sudo chmod 0755 /usr/bin/sync2serial; \
	sudo chmod 0755 /service/sync2serial_daemon/run; \
	sudo chmod 0644 /etc/sync2serial.conf; \

uninstall-service:
	sudo rm -rf /service/sync2serial_daemon; \
	sudo rm -rf /usr/bin/sync2serial.py; \
