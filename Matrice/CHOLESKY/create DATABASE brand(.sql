create table brand(
    idbrand serial,
    brandname varchar(20)
);

create table products(
    idProduct serial,
    name varchar(20),c
    idbrand int,
    available boolean,
    price numeric(10,2)
);

insert into brands(brandname) values('Nike'),('newbalance'),('adidas'),('under armor'),('anta');
insert into brands(idbrand, brandname) VALUES(1,'Nike');

insert into products(name, idbrand, available, price) values('Stan Smith', 3, true, 20000),('Air Max', 1, true, 20000),('Air jord',1,true,20000),('ua',4,true,20000);