
include ../make.def

build: iOSN.h iOSN.xpt 
	cp iOSN.xpt *.js ../components/
	rm -rf manifest
	echo "interfaces iOSN.xpt" >> manifest
	echo "component {D535D85D-D063-44B4-81F3-B521697408CD} facebook.js" >> manifest
	echo "contract		@pinocchio.com/OSNAPI/Facebook;1 {D535D85D-D063-44B4-81F3-B521697408CD}" >> manifest
	echo "category		profile-after-change	FBAPI	@pinocchio.com/OSNAPI/Facebook;1" >> manifest
	echo " " >> manifest
	echo "interfaces	iOSN.xpt" >> manifest
	echo "component		{3E1B79A5-9641-4D54-8CDF-486C5A32499A} twitter.js" >> manifest
	echo "contract		@pinocchio.com/OSNAPI/Twitter;1 {3E1B79A5-9641-4D54-8CDF-486C5A32499A} " >> manifest
	echo "category		profile-after-change	TWTAPI	@pinocchio.com/OSNAPI/Twitter;1" >> manifest

iOSN.h: iOSN.idl
	$(GECKO_SDK_PATH)/bin/xpidl -m header -I$(GECKO_SDK_PATH)/idl/ iOSN.idl 

iOSN.xpt: iOSN.idl
	$(GECKO_SDK_PATH)/bin/xpidl -m typelib -I$(GECKO_SDK_PATH)/idl/ iOSN.idl 

clean :
	rm -f iOSN.xpt iOSN.h *.o *.so
