# git-refactoring-mip-2017-taddo3

# Moj refaktorovany zdrojovy kod bol povodne kod, ktory som odovzdal
# na prpr ako projekt. Tento zdrojovy kod som najskor cely nahral na
# github a potom som ako prve zacal refaktorovat premenne. To som
# docielil ich premonovavanim tak, aby bolo jednoduchsie porozumiet,
# co ktora premenna ma na starost. Nasledne som zrekonstruoval kod,
# aby mal lepsiu modifikovatelnost a testovatelnost. Konkretne som
# to docielil pridanim funkcie, ktora sa dala vyuzit v troch castiach
# mojho kodu, tzn. ze som nemusel mat dany usek kodu trikrat rovnako
# napisany a staci len zavolat funkciu. K testovatelnosti to prispelo
# tak, ze staci otestovat danu vytvorenu funkciu a netreba ju testovat
# na roznych miestach kodu. Taktiez som odstranil nepotrebne cykly
# a jeden switch, bez nich program pracuje o cosi rychlejsie a vystup
# je rovnaky. Uplne na koniec som poupravoval celkovy vyroz kodu pre
# lepsiu citatelnost a odstranil nepotrebne, pripadne doplnil nepostacujuce
# komentare.

# Co sa tyka .gitignore, tak staci, ak budem ignorovat vsetky .exe
# subory. Ostatne, ako napr. predaj.txt sa pocas refaktorovania
# nemenili, tak som ich tam ani davat nemusel, pripadne by som
# mohol najskor ich pushnut na github a potom ich dat do .gitignore.
