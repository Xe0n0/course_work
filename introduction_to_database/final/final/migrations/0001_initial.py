# -*- coding: utf-8 -*-
import datetime
from south.db import db
from south.v2 import SchemaMigration
from django.db import models


class Migration(SchemaMigration):

    def forwards(self, orm):
        # Adding model 'Restaurant'
        db.create_table(u'final_restaurant', (
            (u'id', self.gf('django.db.models.fields.AutoField')(primary_key=True)),
            ('name', self.gf('django.db.models.fields.CharField')(max_length=255)),
            ('cuisine', self.gf('django.db.models.fields.CharField')(max_length=255, blank=True)),
            ('location', self.gf('django.db.models.fields.CharField')(max_length=255)),
            ('landmark', self.gf('django.db.models.fields.CharField')(max_length=255, blank=True)),
            ('phone', self.gf('django.db.models.fields.CharField')(max_length=75, blank=True)),
            ('opentime', self.gf('django.db.models.fields.CharField')(max_length=75)),
        ))
        db.send_create_signal(u'final', ['Restaurant'])

        # Adding model 'Rate'
        db.create_table(u'final_rate', (
            (u'id', self.gf('django.db.models.fields.AutoField')(primary_key=True)),
            ('flavor', self.gf('django.db.models.fields.IntegerField')(default=0)),
            ('service', self.gf('django.db.models.fields.IntegerField')(default=0)),
            ('environment', self.gf('django.db.models.fields.IntegerField')(default=0)),
            ('star', self.gf('django.db.models.fields.IntegerField')(default=0)),
            ('comment', self.gf('django.db.models.fields.TextField')(blank=True)),
        ))
        db.send_create_signal(u'final', ['Rate'])


    def backwards(self, orm):
        # Deleting model 'Restaurant'
        db.delete_table(u'final_restaurant')

        # Deleting model 'Rate'
        db.delete_table(u'final_rate')


    models = {
        u'final.rate': {
            'Meta': {'object_name': 'Rate'},
            'comment': ('django.db.models.fields.TextField', [], {'blank': 'True'}),
            'environment': ('django.db.models.fields.IntegerField', [], {'default': '0'}),
            'flavor': ('django.db.models.fields.IntegerField', [], {'default': '0'}),
            u'id': ('django.db.models.fields.AutoField', [], {'primary_key': 'True'}),
            'service': ('django.db.models.fields.IntegerField', [], {'default': '0'}),
            'star': ('django.db.models.fields.IntegerField', [], {'default': '0'})
        },
        u'final.restaurant': {
            'Meta': {'object_name': 'Restaurant'},
            'cuisine': ('django.db.models.fields.CharField', [], {'max_length': '255', 'blank': 'True'}),
            u'id': ('django.db.models.fields.AutoField', [], {'primary_key': 'True'}),
            'landmark': ('django.db.models.fields.CharField', [], {'max_length': '255', 'blank': 'True'}),
            'location': ('django.db.models.fields.CharField', [], {'max_length': '255'}),
            'name': ('django.db.models.fields.CharField', [], {'max_length': '255'}),
            'opentime': ('django.db.models.fields.CharField', [], {'max_length': '75'}),
            'phone': ('django.db.models.fields.CharField', [], {'max_length': '75', 'blank': 'True'})
        }
    }

    complete_apps = ['final']