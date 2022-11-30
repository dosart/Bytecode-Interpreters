# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure("2") do |config|
  config.vm.box = "bento/ubuntu-20.04"
  config.vm.provision "shell", path: "provision.sh"

  config.vm.provider "virtualbox" do |vb|
    vb.name = "ubuntu-2004_for_c"
    # объем оперативной памяти
    vb.memory = 4096
    # количество ядер процессора
    vb.cpus = 4
  end
end
