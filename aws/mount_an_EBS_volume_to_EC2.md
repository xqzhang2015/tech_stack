
# [How To Attach And Mount An EBS Volume To EC2](https://devopscube.com/mount-ebs-volume-ec2-instance/)

### Mount An EBS Volume To EC2 Linux
In this tutorial, we will teach you how to  attach and mount an EBS volume to ec2 linux instances. Follow the steps given below carefully for the setup.

__Step 1__: Head over to EC2 –> Volumes and create a new volume of your preferred size and type.

Note: the EC2 and Volume should be __in the same zone__.

__Step 2__: Select the created volume, right click and select the “attach volume” option.

__Step 3__: Select the instance from the instance text box as shown below.

attach ebs volume

__Step 4__: Now, login to your ec2 instance and list the available disks using the following command.
```
 lsblk
```
The above command will list the disk you attached to your instance.

__Step 5__: Check if the volume has any data using the following command.
```
sudo file -s /dev/xvdb
```
If the above command output shows “/dev/xvdb: data”, it means your volume is empty.
__Step 6__: Format the volume to ext4 filesystem  using the following command.
```
sudo mkfs -t ext4 /dev/xvdb
```
__Step 7__: Create a directory of your choice to mount our new ext4 volume. I am using the name “newvolume”
```
sudo mkdir /export
```
__Step 8__: Mount the volume to “newvolume” directory using the following command.
```
sudo mount /dev/xvdb /export/
```
__Step 9__: cd into newvolume directory and check the disk space for confirming the volume mount.
```
cd /export
df -h .
```
The above command would show the free space in the newvolume directory.

To unmount the volume, you have to use the following command.
```
umount /dev/xvdb
```

### EBS Automount On Reboot

By default on every reboot the  EBS volumes other than root volume will get unmounted. To enable automount, you need to make an entry in the /etc/fstab file.

1. Back up the /etc/fstab file.
```
sudo cp /etc/fstab /etc/fstab.bak
```

2. Open /etc/fstab file and make an entry in the following format.
```
device_name mount_point file_system_type fs_mntops fs_freq fs_passno
```
For example,
```
/dev/xvdb       /export   ext4    defaults,nofail        0       0
```
3. Execute the following command to check id the fstab file has any error.
```
sudo mount -a
```
If the above command shows no error, it means your fstab entry is good.


# References
[How To Attach And Mount An EBS Volume To EC2 Linux Instance](https://devopscube.com/mount-ebs-volume-ec2-instance/)<br/>

[]()<br/>


[]()<br/>


[]()<br/>


[]()<br/>
