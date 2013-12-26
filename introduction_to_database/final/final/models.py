# -*- coding: utf-8 -*-
import re
from time import time

from django.contrib.auth.models import User
from django.db import models
from django.utils.translation import ugettext_lazy as _
from django.utils import timezone
from django.utils.http import urlquote
from django.contrib import admin
from django.core.exceptions import ValidationError
from django.conf import settings
from django.core.validators import validate_slug

from filer.fields.image import FilerImageField
from filer.models import Image
from filer.admin.fileadmin import FileAdmin

p_url = re.compile('http://v\.youku\.com/v_show/id_(.*)\.html')

def validate_space(value):
    if value[0] == ' ' or value[-1] == ' ' :
        raise ValidationError('should not begin or end with space')

def validate_sections(value):
    sec = value.split();
    if len(sec) < 3:
        raise ValidationError('can not be splitted to 3 sections')
    validate_space(value)
    
def validate_tags(value):
    tags = value.strip();
    if len(tags) < 1:
        raise ValidationError('tags should not only contain space')
    validate_space(value)

def validate_url(value):
    if p_url.match(value) is None:
        raise ValidationError('invalid video url')

class Restaurant(models.Model):
    name = models.CharField(max_length=255, blank=False)
    cuisine = models.CharField(max_length=255, blank=True)
    location = models.CharField(max_length=255, blank=False)
    landmark = models.CharField(max_length=255, blank=True)
    phone = models.CharField(max_length=75, blank=True)
    opentime = models.CharField(max_length=75, blank=False)

class Rate(models.Model):
    flavor = models.IntegerField(default=0, blank=False)
    service = models.IntegerField(default=0, blank=False)
    environment = models.IntegerField(default=0, blank=False)
    star = models.IntegerField(default=0, blank=False)
    comment = models.TextField(blank=True)

from django.forms import ModelForm
# class ShowForm(ModelForm):
#     class Meta:
#         model = Show

#     def save(self, *args, **kwargs):

#         commit = kwargs.pop('commit', True)
#         instance = super(ShowForm, self).save(*args, commit = False, **kwargs)
#         if instance.audio_url == '':
#             instance.audio_url = \
#                 '{}{}/output.m3u8'.format(settings.AUDIO_URL, instance.issue)
#         instance.tags = instance.tags.strip()
#         # print >> sys.stderr, instance.audio_url == ''
#         if commit:
#             instance.save()
#         return instance

# class ShowAdmin(admin.ModelAdmin):
#     form = ShowForm

#     def make_published(modeladmin, request, queryset):
#         queryset.update(is_public=True)
#     make_published.short_description = u"发布"

#     def unpublish(modeladmin, request, queryset):
#         queryset.update(is_public=False)
#     unpublish.short_description = u'取消发布'

#     def stop_test(modeladmin, request, queryset):
#         queryset.update(is_testing=False)
#     stop_test.short_description = u'取消测试'

#     def make_testing(modeladmin, request, queryset):
#         queryset.update(is_testing=True)
#     make_testing.short_description = u"发布到测试渠道"
#     list_display = ['title', 'is_public', 'is_testing', 'modified']
#     ordering = ['issue']
#     actions = [make_published, unpublish, make_testing, stop_test]
#     list_filter = ['is_public', 'is_testing', 'modified']

#     def has_delete_permission(self, request, obj=None):
#         return False


# admin.site.register(User)
# admin.site.register(Show, ShowAdmin)
# admin.site.disable_action('delete_selected')
