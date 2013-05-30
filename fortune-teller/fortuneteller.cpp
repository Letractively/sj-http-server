/*
http://sj-http-server.googlecode.com/

Copyright (C) Jakub Wachowski

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/


#include "fortuneteller.h"
#include "loggerfactory.h"
#include "logbuilder.h"
#include <QString>
#include <QByteArray>

namespace SJ {

QStringList FortuneTeller::fortunes;
bool FortuneTeller::fortunesSet = false;

const Logger & FortuneTeller::logger = LoggerFactory::instance().getLogger("sj-fortune-teller-logger");

void FortuneTeller::handleGet(HttpRequest * /* request */, HttpResponse * response) const
{
    QString cookie = getFortune();

    if(logger.isDebugEnabled()) {
        LOG_DEBUG(logger, (LogBuilder("Returning new cookie: ").append(cookie)));
    }

    QString text = "<html><head><title>Fortune cookie</title></head><body><h3>Fortune cookie</h3>" + cookie + "<br><br>"
            "<font size='-1'>Fortune comes from <a href='http://www.fortunecookiemessage.com/'>www.fortunecookiemessage.com</a></font></body></html>";
    QByteArray a;
    a.append(text);
    response->setContentType("text/html");
    response->writeData(a);
}

QString FortuneTeller::name() const {
    return "FortuneTeller";
}

QString FortuneTeller::getFortune()
{
    if(!fortunesSet) {
        fortunes.push_back("The cooler you think you are the dumber you look");
        fortunes.push_back("If you speak honestly, everyone will listen");
        fortunes.push_back("In music, one must think with his heart and feel with his brain.");
        fortunes.push_back("Ganerosity will repay itself sooner than you imagine.");
        fortunes.push_back("good things take time");
        fortunes.push_back("Do what is right, not what you should.");
        fortunes.push_back("To effect the quality of the day is no small achievement.");
        fortunes.push_back("Simplicity and clearity should be the theme in your dress.");
        fortunes.push_back("Virtuous find joy while Wrongdoers find grieve in their actions.");
        fortunes.push_back("Not all closed eye is sleeping, nor open eye is seeing.");
        fortunes.push_back("Bread today is better than cake tomorrow.");
        fortunes.push_back("In evrything there is a piece of truth.But a piece.");
        fortunes.push_back("A feeling is an idea with roots.");
        fortunes.push_back("Man is born to live and not prepare to live");
        fortunes.push_back("It's all right to have butterflies in your stomach. Just get them to fly in formation.");
        fortunes.push_back("If you don t give something, you will not get anything");
        fortunes.push_back("The harder you try to not be like your parents, the more likely you will become them");
        fortunes.push_back("Someday everything will all make perfect sense");
        fortunes.push_back("you will think for yourself when you stop letting others think for you");
        fortunes.push_back("Everything will be ok. Don't obsess. Time will prove you right, you must stay where you are.");
        fortunes.push_back("Let's finish this up now, someone is waiting for you on that");
        fortunes.push_back("The finest men like the finest steels have been tempered in the hottest furnace.");
        fortunes.push_back("A dream you have will come true");
        fortunes.push_back("The worst of friends may become the best of enemies, but you will always find yourself hanging on.");
        fortunes.push_back("I think, you ate your fortune while you were eating your cookie");
        fortunes.push_back("If u love someone keep fighting for them");
        fortunes.push_back("Do what you want, when you want, and you will be rewarded");
        fortunes.push_back("Let your fantasies unwind...");
        fortunes.push_back("The cooler you think you are the dumber you look");
        fortunes.push_back("Expect great things and great things will come");
        fortunes.push_back("The Wheel of Good Fortune is finally turning in your direction!");
        fortunes.push_back("Don't lead if you won't lead.");
        fortunes.push_back("You will always be successful in your professional career");
        fortunes.push_back("Share your hapiness with others today.");
        fortunes.push_back("It's up to you to clearify.");
        fortunes.push_back("Your future will be happy and productive.");
        fortunes.push_back("Seize every second of your life and savor it.");
        fortunes.push_back("Those who walk in other's tracks leave no footprints.");
        fortunes.push_back("Failure is the mother of all success.");
        fortunes.push_back("Difficulty at the beginning useually means ease at the end.");
        fortunes.push_back("Do not seek so much to find the answer as much as to understand the question better.");
        fortunes.push_back("Your way of doing what other people do their way is what makes you special.");
        fortunes.push_back("A beautiful, smart, and loving person will be coming into your life.");
        fortunes.push_back("Friendship is an ocean that you cannot see bottom.");
        fortunes.push_back("Your life does not get better by chance, it gets better by change.");
        fortunes.push_back("Our duty,as men and women,is to proceed as if limits to our ability did not exist.");
        fortunes.push_back("A pleasant expeience is ahead:don't pass it by.");
        fortunes.push_back("Our perception and attitude toward any situation will determine the outcome");
        fortunes.push_back("They say you are stubborn; you call it persistence.");
        fortunes.push_back("Two small jumps are sometimes better than one big leap.");
        fortunes.push_back("A new wardrobe brings great joy and change to your life.");

        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        fortunesSet = true;

        if(logger.isDebugEnabled()) {
            LogBuilder lb("LoadedCookies are: ");
            lb.append(fortunes,"\n\t ");
            LOG_DEBUG(logger, lb.toString());
        }
    }

    return fortunes[qrand() % fortunes.size()];
}

} //namespace SJ
