# WaterTooHigh

http://www.binarypower.com/2014/07/use-arduino-yun-to-send-emails-simple.html

## Get libraries
Copy latest RGB.h from https://github.com/xTianRoy/RGB.git to your Arduino libraries folder (on computer).

## Install apps needed (linux)
```
opkg update
opkg install ssmtp
mv /etc/ssmtp/ssmtp.conf /etc/ssmtp/ssmtp.bkp
```

ftp ssmtp.conf to /etc/ssmtp/
```
chmod 640 /etc/ssmtp/ssmtp.conf
```

## Test sending email with sender, subject and content
```
echo "From:arduino yun\nSubject: put subject here\nput message body here" | ssmtp myemail@gmail.com
```
