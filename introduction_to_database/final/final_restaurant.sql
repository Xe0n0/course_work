CREATE TABLE `final_restaurant` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL,
  `cuisine` varchar(255) NOT NULL,
  `location` varchar(255) NOT NULL,
  `landmark` varchar(255) NOT NULL,
  `phone` varchar(75) NOT NULL,
  `opentime` varchar(75) NOT NULL,
  `x` int(11) NOT NULL,
  `y` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=1002 DEFAULT CHARSET=utf8;
