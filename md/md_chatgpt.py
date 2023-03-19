import io
import os
import sys
import json
import time
import requests
import platform
from multiprocessing import Pool

# https://www.bilibili.com/video/BV1CN411c7n7
# 代码仅供参考
# 下面要填写自己的api_key
# 如果有不同账号的多个api_key可自动并行画图
all_api_key=[
'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',   
]

fig_path = r'fig'
syst_label = r"情景"
user_label = r"提问"
asst_label = r"回答"
draw_label = r"画图"
endl = '\n\n'
all_role_label = [syst_label, user_label, asst_label]

syst =  lambda s : {"role": "system", "content": s}
user =  lambda s : {"role": "user", "content": s}
assi =  lambda s : {"role": "assistant", "content": s}


user_md = '\n\n' + "## "+ user_label + '\n'
asst_md = '\n' + "## "+ asst_label + '\n'

all_gpt_decorate = [syst, user, assi]

def get_h2_message(mdfile):
    h2_title = []
    h2_line_num = []
    with open(mdfile, 'r', encoding='utf-8') as file:
        lines = file.readlines()
        for i in range(-1, -len(lines), -1):
            line = lines[i]
            if line[0] == "#":
                if line[1] == " " or line == "#\n":
                    break
                elif line[1:3] == "# " :
                    tmp = line[3:].strip()
                    if tmp == draw_label:
                        if h2_line_num == []:
                            draw_message = lines[i+1 :]
                        else:
                            draw_message = lines[i+1 : h2_line_num[-1]]
                        draw_message = ''.join(draw_message).strip()
                        if draw_message != '':
                            return draw_message, [-1]
                    else:
                        h2_title.append(tmp)
                        h2_line_num.append(i)

        num_h2_title = len(h2_title)
        if num_h2_title == 0:
            return [], []

        h2_mark = [-1]*num_h2_title
        for i, title in enumerate(h2_title):
            for k, role in enumerate(all_role_label):
                if role == title:
                    h2_mark[i] = k
                    break
        message = []
        ind = []

        if h2_mark[0] != -1 and h2_line_num[0] != -1:
            tmp = lines[h2_line_num[0]+1:]
            tmp = ''.join(tmp).strip()
            if tmp != '':
                message.append(tmp)
                ind.append(h2_mark[0])

        for i in range(len(h2_mark)-1):
            if h2_mark[i+1] != -1:
                tmp = lines[h2_line_num[i+1]+1 : h2_line_num[i]]
                tmp = ''.join(tmp).strip()
                if tmp != '':
                    message.append(tmp)
                    ind.append(h2_mark[i+1])

    return message, ind

def gpt35(messages, key, mdfile):
    params = {
        "messages": messages,
        "max_tokens": 4000,
        "temperature": 0,
        "model": "gpt-3.5-turbo",
        "stream":True,
    }
    def ct(str):
        ans = json.loads(str)
        return ans['choices'][0]['delta'].get('content','')
    all_res = []
    N = t = k = 0
    head = {"Authorization": f"Bearer {key}", "Content-Type": "application/json"}
    chat_url = "https://api.openai.com/v1/chat/completions"
    with requests.post(chat_url, headers=head, json=params, timeout=60, stream=True) as response:
        for res in response:
            if res and res != '':
                dres = res.decode('utf-8')
                if len(dres) > 6 and dres[:6] == 'data: ':
                    k += 1
                    if k > 1:
                        comb = ''.join(all_res[N:])
                        N = t
                        for line in io.StringIO(comb).readlines():
                            if len(line) > 6 and  line[:6] == 'data: ':
                                line = line[6:]
                                with open(mdfile, 'a', encoding='utf-8') as f:
                                    f.writelines(ct(line))
                all_res.append(dres)
                t += 1
    return

def mkfig(prompt, s, key):
    url = "https://api.openai.com/v1/images/generations"
    head = {"Authorization": f"Bearer {key}", "Content-Type": "application/json"}
    params = {"model": "image-alpha-001", "prompt": prompt, "num_images": 1, 'size':'512x512'}
    # size  ['256x256', '512x512', '1024x1024']
    with requests.post(url, headers=head, json=params, timeout=60) as response:
        res = response.json()
        pic_url = res['data'][0]['url']
    if not os.path.exists(fig_path):
        os.mkdir(fig_path)
    file = requests.get(pic_url)
    now = time.strftime("%Y%m%d%H%M%S", time.localtime())
    filename = r'./' + fig_path + r'/' +str(now) + s + 'chat.png'
    with open(filename, 'wb') as f:
        f.write(file.content)
    return filename

class Gpt(object):
    def __init__(self, mdfile, keys):
        self.message, self.ind = get_h2_message(mdfile)
        self.mdfile = mdfile
        self.keys = keys

    def ps(self, key):
        return mkfig(self.message, key[-3:], key)

    def run(self):
        if self.message == []:
            return
        if self.ind[0] == -1:
            with open(self.mdfile, 'a', encoding='utf-8') as f:
                f.writelines('\n---\n')

            if platform.system().lower()!= 'windows':
                N = len(self.keys)
                with Pool(N) as p:
                    all_figs = p.map(self.ps, self.keys)
                with open(self.mdfile, 'a', encoding='utf-8') as f:
                    for fig in all_figs:
                        f.writelines('![]('+  fig +')\n')
            else:
                fig = self.ps(self.keys[-1])
                with open(self.mdfile, 'a', encoding='utf-8') as f:
                    f.writelines('![]('+  fig +')\n')
            return

        gpt_in = []
        for i in range(-1, -len(self.ind)-1, -1):
            roll_decorate = all_gpt_decorate[self.ind[i]]
            gpt_in.append(roll_decorate(self.message[i]))
        with open(self.mdfile, 'a', encoding='utf-8') as f:
            f.writelines(asst_md)
        gpt35(gpt_in, self.keys[-1], self.mdfile)
        with open(self.mdfile, 'a', encoding='utf-8') as f:
            f.writelines(user_md)


def get_mdfile():
    if len(sys.argv) > 1:
        return str(sys.argv[-1])
    files = os.listdir()
    files = [f for f in files if os.path.isfile(f) and f[-3:]=='.md']
    mtimes = [os.path.getmtime(f) for f in files]
    return files[mtimes.index(max(mtimes))]


mdfile = get_mdfile()
Gpt(mdfile, all_api_key).run() 
