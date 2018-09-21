import smtplib


def sendEmail(score):
    server = smtplib.SMTP('smtp.gmail.com', 587)

    server.ehlo()
    server.starttls()



    #Next, log in to the server
    server.login("yourstuffbrokedude@gmail.com", "123456stuff")

    #Send the mail
    message = 'Subject: {}\n\n{}'.format("Oh no!", "Something is wrong with your motor! \n \n \nOur analysis gives it an error rating of " + str((score)) + ", where anything above 17.5 is considered broken =(")
    server.sendmail("you@gmail.com", "hoshyar@gmail.com", message)

