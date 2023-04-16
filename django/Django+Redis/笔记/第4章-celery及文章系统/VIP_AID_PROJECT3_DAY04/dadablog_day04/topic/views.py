from django.http import JsonResponse
from django.shortcuts import render
from django.views import View
from django.utils.decorators import method_decorator
from tools.logging_dec import logging_check, get_user_by_request
import json
from .models import Topic
from user.models import UserProfile
#异常码 10300-10399

# Create your views here.
class TopicViews(View):

    def make_topics_res(self, author, author_topics):
        #{‘code’:200,’data’:{‘nickname’:’abc’, ’topics’:[{‘id’:1,’title’:’a’, ‘category’: ‘tec’, ‘created_time’: ‘2018-09-03 10:30:20’, ‘introduce’: ‘aaa’, ‘author’:’abc’}]}}
        res = {'code':200, 'data':{}}
        topics_res = []
        for topic in author_topics:
            d = {}
            d['id'] = topic.id
            d['title'] = topic.title
            d['category'] = topic.category
            d['created_time'] = topic.created_time.strftime("%Y-%m-%d %H:%M:%S")
            d['introduce'] = topic.introduce
            d['author'] = author.nickname
            topics_res.append(d)

        res['data']['topics'] = topics_res
        res['data']['nickname'] = author.nickname
        return res

    @method_decorator(logging_check)
    def post(self, request, author_id):
        #{"content":"<p><span style=\"font-weight: bold;\">heiheihei</span><br></p>","content_text":"heiheihei","limit":"public","title":"hahahaha","category":"tec"}
        author = request.myuser
        #取出前端数据
        json_str = request.body
        json_obj = json.loads(json_str)
        title = json_obj['title']
        content = json_obj['content']
        content_text = json_obj['content_text']
        introduce = content_text[:30]
        limit = json_obj['limit']
        category = json_obj['category']
        if limit not in ['public', 'private']:
            result = {'code':10300, 'error':'The limit error~'}
            return JsonResponse(result)

        #创建topic数据
        Topic.objects.create(title=title, content=content, limit=limit,category=category,introduce=introduce, author=author)

        return JsonResponse({'code':200})


    def get(self, request, author_id):

        #访问者 visitor
        #当前被访问博客的博主 author
        try:
            author = UserProfile.objects.get(username=author_id)
        except Exception as e:
            result = {'code':10301, 'error':'The author is not existed'}
            return JsonResponse(result)

        visitor = get_user_by_request(request)
        visitor_username = None
        if visitor:
            visitor_username = visitor.username

        # /v1/topics/guoxiaonao
        # /v1/topics/guoxiaonao?category=[tec|no-tec]
        category = request.GET.get('category')

        if category in ['tec', 'no-tec']:

            if visitor_username == author_id:
                #博主访问自己博客
                author_topics = Topic.objects.filter(author_id=author_id, category=category)
            else:
                author_topics = Topic.objects.filter(author_id=author_id, limit='public', category=category)
        else:
            if visitor_username == author_id:
                #博主访问自己博客
                author_topics = Topic.objects.filter(author_id=author_id)
            else:
                author_topics = Topic.objects.filter(author_id=author_id, limit='public')


        res = self.make_topics_res(author, author_topics)
        return JsonResponse(res)

