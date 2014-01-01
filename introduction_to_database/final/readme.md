#数据库概论 final
##简介

本程序使用 Python 开发，使用了 Python 的 Django 框架，用于简化 Web 部分实现。数据库采用了 MySQL 。

### ER 图及 关系模式表

在根目录下 `final_models.png` 为后创建的模式, `final.png` 为包括框架默认模式的 ER 图。
相关 sql 代码在 `final/sql` 下

### 示例数据

在 `final/*_data.sql` 内，可以直接运行插入数据。

## 使用

* Requirements

	* Python 2.7.x
	* Django 1.5.x
	* MySQL-python
	* South
	* django-suit
	* MySQL


* 配置环境信息

   在 `local_settings.py` 中填入正确的变量，如
   
   ```
        STATIC_ROOT = 'pathto/final/final/static/'
        
        STATICFILES_DIRS = (
        )
        
        TEMPLATE_DIRS = (
            'pathto/final/final/template/',
        )
        
        DATABASES = {
            'default': {
                'ENGINE': 'django.db.backends.mysql',
                'NAME': 'test2',
                'USER': 'root',
                'PASSWORD': 'password',
                'HOST': '', #default to 127.0.0.1
                'PORT': '', #default to 3306
            }
        }
   ```
   
* 在数据库中创建对应表
	
	i. 首先运行 `python manage.py syncdb` 将会同步 `Django` 框架对应表格。
	
	ii. 运行 `python manage.py migrate final` 讲会把 `final/migrate` 文件夹下 SQL 语句同步入数据库中。也可手动运行附带 `sql` 文件夹里的语句。如有需要请参考 `South` 文档。
	
	iii. 将 `sql` 文件夹下的视图和触发器输入数据库。

* 运行

	直接运行 `python manage.py runserver` 启动开发服务器，即可访问 `127.0.0.1:8000`。
	
## 程序说明

1. 目录结构
	
	* `urls.py` 包含了 url 到 web 程序代码的映射。
	
	b. `views.py` 包含了全部的 web 程序代码。对执行的过程采用接口继承的方式重组了内容，定义了两个基本过程为 `JSONView` 与 `AjaxListView`。
	
	c. `template` 文件夹包含了 web 程序渲染内容使用的模板，`template/src` 文件夹是手写模板时为了加快开发采用的上层语言的源码。我使用的是 `jade` (Node Template Engine)，基于 Node.js 。如果要编译需要安装 Node.js。
	
	d. `static` 文件夹包含了使用到的 js 与 css 文件，其中 `bower_components` 文件夹是使用 `Bower` (A package manager for the web by Twitter) 管理的 Web 前端依赖库文件夹。我用 `Bower` 安装了 `jQuery`, `Bootstrap`, `Bootstrap Paginator` 。`Bootstrap` 用于快速构建样式，`Bootstrap Paginator` 用于分页样式。
	
2. 程序实现
	
	* 评论、换页、注册、登录全部采用了 Ajax 异步请求。
	
	f. 评论次数控制采用数据库 trigger 抛出异常的方式。
	
	g. 视图使用的是 MySQL View 的 TEMPTABLE 算法。MySQL 没有提供物化视图的办法，查阅资料发现有用 Trigger 手动实现的但是过于麻烦。使用到视图的部分是计算一个餐厅的平均评分。
	
	* 计算临近餐馆通过计算经纬度实现，存储为单位为千分之一度。由于数据有限演示时临近的定义较宽泛，可以更改 `rest_detail.html` 中 `json_url` 的数字参数，如改为 `100/json`
	
	* xml 可以通过餐厅页面的导出按钮导出
	
