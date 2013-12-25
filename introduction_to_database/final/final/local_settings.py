# DATABASE_ENGINE = 'sqlite3'
# DATABASE_NAME = '/tmp/djangodb'
# DATABASE_USER = ''
# DATABASE_PASSWORD = ''
# DATABASE_HOST = ''
# DATABASE_PORT = ''
STATIC_ROOT = '/Users/wuhaotian/Projects/LJSW_Server/static'
MEDIA_ROOT = '/Users/wuhaotian/Projects/LJSW_Server/media'
STATICFILES_DIRS = (
        '/Users/wuhaotian/Projects/LJSW_Server/media',
    # Put strings here, like "/home/html/static" or "C:/www/django/static".
    # Always use forward slashes, even on Windows.
    # Don't forget to use absolute paths, not relative paths.
)

# # Required for Django Debug Toolbar and other things.
# INTERNAL_IPS = ('127.0.0.1',)
DATABASES = {
    'default': {
        'ENGINE': 'django.db.backends.mysql', # Add 'postgresql_psycopg2', 'mysql', 'sqlite3' or 'oracle'.
        'NAME': 'test',                      # Or path to database file if using sqlite3.
        # The following settings are not used with sqlite3:
        'USER': 'wuhaotian',
        'PASSWORD': 'cada2009',
        'HOST': '162.105.74.252',                      # Empty for localhost through domain sockets or '127.0.0.1' for localhost through TCP.
        'PORT': '',                      # Set to empty string for default.
    }
}

