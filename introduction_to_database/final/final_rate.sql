CREATE TABLE `final_rate` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `flavor` int(11) NOT NULL,
  `service` int(11) NOT NULL,
  `environment` int(11) NOT NULL,
  `star` int(11) NOT NULL,
  `comment` longtext NOT NULL,
  `user_id` int(11) NOT NULL,
  `restaurant_id` int(11) NOT NULL,
  `datetime` datetime NOT NULL,
  PRIMARY KEY (`id`),
  KEY `final_rate_6340c63c` (`user_id`),
  KEY `final_rate_be4c8f84` (`restaurant_id`),
  CONSTRAINT `restaurant_id_refs_id_2f9cd607ebe34c8e` FOREIGN KEY (`restaurant_id`) REFERENCES `final_restaurant` (`id`) ON DELETE CASCADE,
  CONSTRAINT `user_id_refs_id_5da62a6f3abc60f1` FOREIGN KEY (`user_id`) REFERENCES `auth_user` (`id`) ON DELETE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=1038 DEFAULT CHARSET=utf8;
