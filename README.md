## 注意

源代码在qt中无法直接运行

因为db_operator类的init函数中的数据库信息为空

![image](https://github.com/HOWILLMAKEIT/-C-/assets/157001241/c0bae388-7485-44ba-98e6-47dd902a3163)

如果想要正确运行可以在本地建一个相同的数据库

数据库信息如下：

数据库名：addressbook

联系人表：contacts

账户表：accounts

contacts表相应设定：

![image](https://github.com/HOWILLMAKEIT/-C-/assets/157001241/f1567b68-31af-4b08-be94-b9ed3cf955df)

其中PK表示主键、NN表示非空（NOT NULL）、UQ表示unique、AI表示自增

accounts表相应设定：

![image](https://github.com/HOWILLMAKEIT/-C-/assets/157001241/0bc85841-3b78-495f-b26e-bfb55de88787)

外键设置（重要）

将accounts的user_id字段的外键设置为accounts表的id字段，

同时将On Update和 On Delete 都设定为CASCADE

这样数据库就建好了，接着在qt中填写数据库的相关信息就可以正常运行程序

## 资源文件下载
链接: https://pan.baidu.com/s/1YvUgyTWtfwXwyEoDYtsUKA 提取码: puhh
下载后在QT中添加resource文件夹，就可以正常显示背景图片以及发出各种音效。


## 视频展示

【【华南理工24C++】乌萨奇通讯录-云端数据库、可视化界面、可发送邮件】https://www.bilibili.com/video/BV1cf421R7pf?vd_source=50cd1a4c87dfd3bdc7a70a5d22a771ed

