#!/usr/bin/env bash
function vpn.start() {
sudo pptpsetup --create vpn --server 172.16.41.41 --username cidi --password cidi --start
sudo route add default dev ppp0
echo nameserver 172.16.201.221 | sudo tee /etc/resolv.conf 
echo nameserver 172.16.201.223 | sudo tee -a /etc/resolv.conf
}

function vpn.stop() {
for i in $(ps -ef | grep pptp | awk '{print $2}'); do sudo kill -9 $i; done
echo nameserver 172.16.201.220 | sudo tee /etc/resolv.conf 
echo nameserver 172.16.201.222 | sudo tee -a /etc/resolv.conf
}

function show_use {
    echo -en "当需要加速访问github dockers等外网资源时，启动vpn.请运行:"
    echo -en " bash vpn.ubuntu.pptp.sh start \n"
    echo -en "不需要加速访问github dockers等外网资源，或者网络有问题时，停止vpn.请运行:" 
    echo -en "bash vpn.ubuntu.pptp.sh stop \n"
}

if [[ $1 == start ]]
then
    ping -c 1 172.16.41.41 > /dev/null
    if [[ $? -eq 0 ]]
    then
        vpn.start
        echo 已经连上VPN加速服务器
    else
        echo 连不上VPN加速服务器
    fi
elif [[ $1 == stop ]]
then
    vpn.stop
    echo 已停止vpn连接
else
   show_use
fi

cd .
