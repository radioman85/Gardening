# Gardening
Gardening

In the end of the day (or next few years...), our garden will be remotely controlled from home :-)

To clone this project:
git clone https://github.com/radioman85/Gardening.git

### To add changes:
git add <filename>  
git commit -m "\<your comment\>"  
git push origin master  
user name: \<user name\>  
user password: \<*********\>  


### Install TTN Sender (LoRaWAN Node on Raspberry)
https://github.com/verschwoerhaus/ttn-ulm-node-dragino/tree/master/ttnsender

You may need also the "bcm2835" library:

sudo apt-get install html-xml-utils
mkdir -p bcm2835 && (wget -qO - `curl -sL http://www.airspayce.com/mikem/bcm2835 | hxnormalize -x -e | hxselect -s '\n' -c "div.textblock>p:nth-child(4)>a:nth-child(1)"` | tar xz --strip-components=1 -C bcm2835 )
cd bcm2835
./configure
make
sudo make install

