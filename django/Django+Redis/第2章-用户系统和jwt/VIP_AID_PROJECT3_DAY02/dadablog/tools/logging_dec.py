

def logging_check(func):
    def wrap(request, *args, **kwargs):

        #获取token request.META.get('HTTP_AUTHORIZATION')
        #校验token
        #失败， code 403  error: Please login

        return func(request, *args, **kwargs)
    return wrap