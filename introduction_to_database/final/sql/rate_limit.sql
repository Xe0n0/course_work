delimiter //
drop trigger if exists rate_limit//
create trigger rate_limit before insert on final_rate
for each row
begin
declare rcount int;
select count(*) from final_rate
where user_id = new.user_id and restaurant_id = new.restaurant_id and `datetime` > date_add(now(), interval -10 minute)
into rcount;
if rcount >= 10 then signal sqlstate '45000'
set message_text = 'TOO_MANY_RATE', mysql_errno = 1001;
end if;
end//
