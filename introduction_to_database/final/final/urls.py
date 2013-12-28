from django.conf.urls import patterns, include, url
from django.contrib import admin
from views import TopView, HotView, NearbyView, RestView, RatingsListView

admin.autodiscover()

urlpatterns = patterns('',
    url(r'^$', 'final.views.home', name='home'),
    url(r'^login', 'final.views.login', name='login'),
    url(r'^eatings/top.json', TopView.as_view(), name='top'),
    url(r'^eatings/hot.json', HotView.as_view(), name='hot'),
    url(r'^eatings/nearby.json', NearbyView.as_view(), name='nearby'),

    url(r'^eating/(?P<pk>\d+)/$', RestView.as_view(), name='rest'),
    url(r'^eating/(?P<pk>\d+)/ratings.json$', RatingsListView.as_view()),
    # url(r'^final/', include('final.foo.urls')),

    # Uncomment the admin/doc line below to enable admin documentation:
    # url(r'^admin/doc/', include('django.contrib.admindocs.urls')),

    url(r'^admin/', include(admin.site.urls)),
)
