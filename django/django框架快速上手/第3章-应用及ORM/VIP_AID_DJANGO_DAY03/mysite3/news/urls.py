from django.urls import path
from . import views

urlpatterns = [
    #http://127.0.0.1:8000/news/index
    path('index', views.index_view)


]