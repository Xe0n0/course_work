CREATE VIEW `test2`.`final_overall` AS  select final_restaurant.id as restaurant_id , count(distinct final_rate.id) as count,avg(star + service +
environment) as total from final_rate, final_restaurant where final_rate.restaurant_id = final_restaurant.id group by final_restaurant.id;
