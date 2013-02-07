APP_NAME = sync2serial
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
	sudo cp bin/$(APP_NAME) /usr/bin/$(APP_NAME); \
	sudo chmod 0755 /usr/bin/$(APP_NAME); \
	sudo mkdir -m0755 -p /service/$(APP_NAME)_daemon; \
	sudo cp -r service/* /service/$(APP_NAME)_daemon/; \
	sudo chmod 0755 /service/$(APP_NAME)_daemon/run; \
	sudo chmod 0755 /service/$(APP_NAME)_daemon/log/run; \
	if [ ! -e /etc/$(APP_NAME).conf ]; then \
		sudo cp conf/$(APP_NAME).conf /etc; \
		sudo chmod 0644 /etc/$(APP_NAME).conf; \
	fi; \

uninstall-service:
	sudo rm -rf /service/$(APP_NAME)_daemon; \
	sudo rm -rf /usr/bin/$(APP_NAME); \
