from django.conf.urls import patterns, include, url
from django.contrib import admin
from views import TopView, HotView, HotListView, NearbyView, RestView, \
    RatingsListView, RateCreate, RateExport, UserCreate, NearbyView, \
    NearbyListView

admin.autodiscover()

from django.contrib.auth.decorators import login_required

urlpatterns = patterns('',
    url(r'^$', 'final.views.home', name='home'),
    url(r'^login', 'final.views.login', name='login'),
    url(r'^signup', UserCreate.as_view(), name='signup'),
    url(r'^logout', 'final.views.logout', name='logout'),

    url(r'^eatings/top.json', TopView.as_view(), name='top'),
    url(r'^eatings/hot.json', HotListView.as_view()), 
    url(r'^hot/', login_required(HotView.as_view()), name='hot'),

    url(r'^eating/(?P<pk>\d+)/$', RestView.as_view(), name='rest'),
    url(r'^eating/(?P<pk>\d+)/ratings.json$', RatingsListView.as_view()),

    url(r'^eating/(?P<pk>\d+)/rate/$', RateCreate.as_view(), name='rate'),
    url(r'^eating/(?P<pk>\d+)/xml/$', RateExport.as_view(), name='rate_xml'),
    url(r'^eating/(?P<pk>\d+)/nearby/$', NearbyView.as_view()),
    url(r'^eating/(?P<pk>\d+)/nearby/(?P<distance>\d+)/json', NearbyListView.as_view()),
    # url(r'^final/', include('final.foo.urls')),

    # Uncomment the admin/doc line below to enable admin documentation:
    # url(r'^admin/doc/', include('django.contrib.admindocs.urls')),

    url(r'^admin/', include(admin.site.urls)),
)
