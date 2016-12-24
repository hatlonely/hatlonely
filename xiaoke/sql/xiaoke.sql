CREATE USER 'hatlonely'@'192.168.0.%' IDENTIFIED BY '12345678';
CREATE DATABASE IF NOT EXISTS hatlonely DEFAULT CHARSET utf8 COLLATE utf8_general_ci;
GRANT ALL PRIVILEGES ON hatlonely.* TO 'hatlonely'@'192.168.0.%';
GRANT ALL PRIVILEGES ON hatlonely.* TO 'hatlonely'@'localhost';

USE hatlonely;
CREATE TABLE IF NOT EXISTS docs (
    `id` Int NOT NULL AUTO_INCREMENT,
    `title` varchar(512) NOT NULL,
    `md5` char(32) NOT NULL,
    `views` INT NOT NULL DEFAULT 0,
    PRIMARY KEY (`id`),
    UNIQUE KEY `md5` (`md5`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8;

USE hatlonely;
CREATE TABLE IF NOT EXISTS ones (
    `id` INT NOT NULL AUTO_INCREMENT,
    `hashcode` BIGINT NOT NULL,
    `one` varchar(10240) NOT NULL,
    PRIMARY KEY (`id`),
    UNIQUE KEY `hashcode` (`hashcode`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8;
