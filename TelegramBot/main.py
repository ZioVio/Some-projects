import requests
from time import sleep


token = '624807853:AAFpoKOjWkpGqXcbtCdhRAoORvllck13X8A'
url = "https://api.telegram.org/bot"+ token + "/"


def get_updates_json(request):  
    response = requests.get(request + 'getUpdates')
    return response.json()


def last_update(data):  
    results = data['result']
    total_updates = len(results) - 1
    return results[total_updates]


def get_chat_id(update):  
    chat_id = update['message']['chat']['id']
    return chat_id

def send_mess(chat, text):  
    params = {'chat_id': chat, 'text': text}
    response = requests.post(url + 'sendMessage', data=params)
    return response

def main():  
    updates = last_update(get_updates_json(url))
    update_id = updates['update_id']
    text_to_send = updates['message']['text']
    while True:
        curr_upd = last_update(get_updates_json(url))
        if update_id == curr_upd['update_id']:
            text_to_send = curr_upd['message']['text']
            if curr_upd['message']['from']['username'] == 'ZioSmith':
                send_mess(get_chat_id(curr_upd), 'Tolko Andrey poluchaet eto soobshchenie')
            send_mess(get_chat_id(curr_upd), text_to_send)
            print(text_to_send)
            update_id += 1
        sleep(1)      

if __name__ == '__main__':  
    main()

