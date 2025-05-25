#2e7216e1b4ad4be887983cd90f3b088d

import smtplib
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
import requests

# 1. Sending Email
def send_email(sender_email, receiver_email, subject, body, smtp_server, port, login, password):
    try:
        # Set up the MIME
        message = MIMEMultipart()
        message['From'] = sender_email
        message['To'] = receiver_email
        message['Subject'] = subject
        message.attach(MIMEText(body, 'plain'))

        # Connect to SMTP server
        with smtplib.SMTP(smtp_server, port) as server:
            server.starttls()
            server.login(login, password)
            server.sendmail(sender_email, receiver_email, message.as_string())
        print("Email sent successfully.")
    except Exception as e:
        print(f"Failed to send email: {str(e)}")

# 2. Reading News (using NewsAPI)
def get_news(api_key, query='technology'):
    try:
        url = f"https://newsapi.org/v2/everything?q={query}&apiKey={api_key}"
        response = requests.get(url)
        news_data = response.json()

        if news_data.get("status") == "ok":
            articles = news_data.get("articles", [])
            for i, article in enumerate(articles[:5]):  # Fetch top 5 articles
                print(f"{i+1}. {article['title']}")
                print(f"   Source: {article['source']['name']}")
                print(f"   URL: {article['url']}\n")
        else:
            print("Failed to fetch news.")
    except Exception as e:
        print(f"Error while fetching news: {str(e)}")

# Example Usage with Input
if __name__ == "__main__":
    # Send Email Input
    print("Send an Email")
    sender = input("Enter your email: ")
    receiver = input("Enter receiver email: ")
    subject = input("Enter the subject: ")
    body = input("Enter the message body: ")
    smtp_server = input("Enter the SMTP server (e.g., smtp.gmail.com): ")
    smtp_port = int(input("Enter the SMTP port (e.g., 587): "))
    login = input("Enter your email login: ")
    password = input("Enter your email password: ")  # Use securely in production
    send_email(sender, receiver, subject, body, smtp_server, smtp_port, login, password)

    # Fetch News Input
    print("\nFetch News")
    api_key = input("Enter your NewsAPI key: ")
    query = input("Enter news topic (e.g., technology): ")
    get_news(api_key, query)