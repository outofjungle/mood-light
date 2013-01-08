APP_NAME = mood-light
PYSERIAL_URL = http://pypi.python.org/packages/source/p/pyserial/pyserial-2.6.tar.gz
PYSERIAL_DIR = $(subst .tar.gz,,$(notdir $(PYSERIAL_URL)))

.PHONY: install-pyserial

install-pyserial: 
	curl $(PYSERIAL_URL) | tar -xz;\
	cd $(PYSERIAL_DIR); sudo python setup.py install;\

create-log-file:
	sudo mkdir /var/log/$(APP_NAME);\
	sudo chown pi:users /var/log/$(APP_NAME);\

