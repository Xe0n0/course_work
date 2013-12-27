import sys

from django.shortcuts import *
from django.template import RequestContext
from django.http import HttpResponse
from django.contrib.auth.decorators import login_required
from django.contrib.auth import authenticate, login as django_login
from django.template.loader import get_template
from django.template import Context
from json import dumps

from models import Rate, Restaurant as Rest

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
