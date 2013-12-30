import sys
from json import dumps

from django.shortcuts import *
from django.template import RequestContext
from django.http import HttpResponse, HttpResponseRedirect
from django.contrib.auth.decorators import login_required
from django.contrib.auth import authenticate, login as django_login
from django.template.loader import get_template
from django.template import Context
from django.views.generic import View, TemplateView


from models import Rate, Restaurant as Rest, User

def json_response(func):
    def inner(request=None, *args, **kwargs):
        status_code = 200
        response = func(request, *args, **kwargs)
        content = response
        if isinstance(response, tuple):
            content = response[0]
            status_code = response[1]
        # print >> sys.stderr, content
        return HttpResponse(dumps(content, ensure_ascii=False, separators=(',',':')),
          mimetype="application/json", status=status_code)
    return inner

@login_required
def home(request):
    return render_to_response('index.html', {}, context_instance=RequestContext(request))

def login(request):
    if request.method == 'POST':
        user = authenticate(username = request.POST.get('username', ''), password=request.POST.get('password', ''))

        if user and user.is_active:
            django_login(request, user)
            return render_to_response('index.html', {}, context_instance=RequestContext(request))

    return render_to_response('login.html', {}, context_instance=RequestContext(request))

@json_response
def top(request):

  array = Rest.objects.all()

  per = 20

  pagecount = array.count() / per

  pageid = request.POST.get('pageid', '1')

  offset = int(pageid) * 20

  context = { 'array': array[offset - 20 : offset] }
    
  t = get_template("index_content.html")
  content = t.render(Context(context))
  
  return {
      'content': content,
      'pagecount': pagecount,
  }

from django.views.generic.detail import DetailView
from django.forms import ModelForm


class UserForm(ModelForm):
    class Meta:
        model = User

    

class RateForm(ModelForm):
    class Meta:
        model = Rate
        exclude = ('user', 'restaurant')


class RestView(DetailView):
    model = Rest
    template_name = 'rest_detail.html'

from django.db import DatabaseError


class JSONView(View):
    
    def post(self, request, *args, **kwargs):
        
        self.request = request
        self.args = args
        self.kwargs = kwargs

        content = self.get_context()

        return HttpResponse(dumps(content, ensure_ascii=False, separators=(',',':')),
                mimetype="application/json")

class RateExport(View):
    
    def get(self, request, *args, **kwargs):

        r = Rest.objects.get(id = kwargs['pk'])

        context = {
                'object': r,
                'count': r.rate_set.all().count,
                'rate_set': r.rate_set.all(),
        }
        return render_to_response('rest.xml', context,
                context_instance=RequestContext(request), mimetype='application/xml')

class RateCreate(JSONView):
    form = RateForm

    def get_context(self):

        f = self.form(self.request.POST)
        obj = f.save(commit=False)
        obj.user = self.request.user
        r = Rest.objects.get(id = self.kwargs['pk'])
        obj.restaurant = r
        err = f.errors

        try:
            f.save()
            return {
                'status': 0,
                'message': '''<div class="alert alert-success alert-dismissable">
                  <button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>
                    <strong>Well done!</strong> You have rated the restaurant!
                    </div>'''
            }

        except DatabaseError, e:
            err = e
        return {
                'status': -1,
                'message': '''<div class="alert alert-danger alert-dismissable">
                  <button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>
                    <strong>Oops!</strong> You have rated the restaurant 10 times within 10 minutes!
                    </div>''',
        }

class UserCreate(View):

    def get_context(self):

        u = UserForm(self.request.POST)
        try:
            u.save()
            django_login(request, u)
            return {
                    'status': 0,
                    'message': '',
                    }
        except:
            pass

        return {
                'status': -1,
                'message': '''<div class="alert alert-danger alert-dismissable">
                  <button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>
                    <strong>Oops!</strong> The username may have been used. Try again!
                    </div>'''
        }


class AjaxListView(JSONView):

    template = "index_content.html"
    per = 20.0

    def query_set(self):
        return Rest.objects.all()
    
    def get_page_context(self, request):
        
        array = self.query_set()

        try:
            pagecount = array.count() / self.per
        except:
            pagecount = len(list(array)) / self.per

        import math

        pagecount = int(math.ceil(pagecount))

        pageid = request.POST.get('pageid', '1')

        offset = int(pageid) * int(self.per)

        context = { 'array': array[offset - int(self.per) : offset] }

        t = get_template(self.template)
        content = t.render(Context(context))

        context = {
            'content': content,
            'pagecount': pagecount,
        }
        return context

    def get_context(self):
        return self.get_page_context(self.request)


class TopView(AjaxListView):
    template = "index_content.html"

    def query_set(self):
        return Rest.objects.raw('''SELECT * FROM final_overall
                left join final_restaurant on restaurant_id = id
                ORDER BY total DESC LIMIT 10''')
        
class HotView(TemplateView):
    template_name = "hot.html"

class HotListView(AjaxListView):
    template = "index_content.html"

    def query_set(self):
      return Rest.objects.raw('''select * from final_restaurant
        left join final_overall on restaurant_id = id
        where count > (select avg(count) from final_overall) order by count desc''')

class NearbyView(AjaxListView):
    pass

class RatingsListView(AjaxListView):
    template = "ratings_content.html"

    def query_set(self):
      return Rest.objects.get(id = self.kwargs['pk']).rate_set.all()


