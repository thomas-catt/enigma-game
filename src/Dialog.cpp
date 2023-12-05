/* Dialog.cpp *
 * This file will contain all the dialogs (NPC talks with the player).
 *
 * */

Dialog playerBeforeCave() {
    Dialog d;
    d.title = "Interesting cave...";
    d.identifier = DIALOG_PLAYER_BEFORE_CAVE;
    d.messages[0].speaker = playerChar;
    d.messages[0].message = "I don't want to enter this cave.";
    d.messages[1].speaker = playerChar;
    d.messages[1].message = "But I came all the way here...";
    d.messages[2].speaker = playerChar;
    d.messages[2].message = "Would be a shame if I walk back discovering nothing.";
    d.messages[3].speaker = playerChar;
    d.messages[3].message = "I'll just walk inside and get back out quickly.";

    return d;
}

Dialog guideIntro() {
    Dialog d;
    d.title = "Talk to stranger";
    d.messages[0].speaker = guideChar;
    d.messages[0].message = "Hello Traveler! I hope you're doing good.";

    return d;
}

Dialog testDialog() {
    Dialog d;
    d.title = "Talk to ???";
    d.messages[0].speaker = guideChar;
    d.messages[0].message = "Hello Traveler! I hope you're doing good.";
    d.messages[1].speaker = guideChar;
    d.messages[1].message = "It seems my students do not fully understand what it means to wield the blade.";
    d.messages[2].speaker = guideChar;
    d.messages[2].message = "Perhaps you could show them what you know?";

    return d;
}

Dialog noGoingBackDialog() {
    Dialog d;
    d.identifier = DIALOG_GUIDE_FIRST;
    d.title = "No going back...";
    if (countKeys() == 3) {
        d.messages[0].speaker = guideChar;
        d.messages[0].message = "So you finally collected all the keys.";
        d.messages[1].speaker = playerChar;
        d.messages[1].message = "Yep.";
        d.messages[2].speaker = guideChar;
        d.messages[2].message = "Impressive.";
        d.messages[3].speaker = guideChar;
        d.messages[3].message = "Well then I mustn't behave as an obstacle in your path.";
        d.messages[4].speaker = guideChar;
        d.messages[4].message = "May you enjoy freedom.";
    } else {
        d.messages[0].speaker = guideChar;
        switch (countKeys()) {
            case 0:
                d.messages[0].message = "It's known that coming out of this place is not easy. Three keys are required to return to the overworld.";
                d.messages[1].speaker = guideChar;
                d.messages[1].message = "Walk around and find all the keys you need to get back out.";
                d.messages[2].speaker = guideChar;
                d.messages[2].message = "Come back to me whenever you're unsure about anything.";
                break;
            case 1:
                d.messages[0].message = "Great, you obtained your first key. Continue your adventure!";
                break;
            case 2:
                d.messages[0].message = "Two down, one more to go. Keep up the good work, you're almost there.";
                break;
        }
    }

    return d;
}

Dialog rockDialog() {
    Dialog d;
    d.title = "Rock";
    d.identifier = DIALOG_ROCK_GAME;
//    d.messages[0].speaker = rockChar;
//    d.messages[0].message = "Hello I am rock.";
//    d.messages[1].speaker = guideChar;
//    d.messages[1].message = "It seems my students do not fully understand what it means to wield the blade.";
//    d.messages[2].speaker = rockChar;
//    d.messages[2].message = "shut up this is my dialog not yours";
//    d.messages[3].speaker = guideChar;
//    d.messages[3].message = "sorry";
//    d.messages[4].speaker = rockChar;
//    d.messages[4].message = "okay so i have this uhh rock game thing, play it pls.";
    d.messages[0].speaker = rockChar;
    d.messages[0].message = "Up you climb, youngling, to where the key resides. Beware my rocky path, for it yields only to those who persist.";
    d.messages[1].speaker = emptyChar;
    d.messages[1].message = "Climb up the rocky hill without touching any obstacles!";

    return d;
}

Dialog horseDialog() {
    Dialog d;
    d.title = "Horse";
    d.identifier = DIALOG_PLATFORMER_GAME;
//    d.messages[0].speaker = rockChar;
//    d.messages[0].message = "Hello I am rock.";
//    d.messages[1].speaker = guideChar;
//    d.messages[1].message = "It seems my students do not fully understand what it means to wield the blade.";
//    d.messages[2].speaker = rockChar;
//    d.messages[2].message = "shut up this is my dialog not yours";
//    d.messages[3].speaker = guideChar;
//    d.messages[3].message = "sorry";
//    d.messages[4].speaker = rockChar;
//    d.messages[4].message = "okay so i have this uhh rock game thing, play it pls.";
    d.messages[0].speaker = platformerChar;
    d.messages[0].message = "Run from me.";
    d.messages[1].speaker = emptyChar;
    d.messages[1].message = "Run from the horse approaching you!";

    return d;
}

Dialog cipherDialog() {
    Dialog d;
    d.title = "Cipher";
    d.identifier = DIALOG_CIPHER_GAME;

    d.messages[0].speaker = cipherChar;
    d.messages[0].message = "Greetings traveller. What an honor to be visited by such an elegant creature.";
    d.messages[1].speaker = cipherChar;
    d.messages[1].message = "However I present you with a challange.";
    d.messages[2].speaker = cipherChar;
    d.messages[2].message = "My domain is full of mind boggling challanges. Solve them, in reward of doing so I shall grant you with the final key you're looking for.";
    d.messages[3].speaker = emptyChar;
    d.messages[3].message = "Solve the ciphers to obtain the key.";


    return d;
}

Dialog cipherProgressDialog() {
    Dialog d;
    int totalCompletedCiphers = puzzleCipherCompleted + vigenereCipherCompleted;

    d.messages[0].speaker = emptyChar;
    d.messages[0].message = "";
    return d;
}

Dialog lostMiniGameDialog(Minigame minigame) {
    Dialog d;
    d.identifier = DIALOG_MINIGAME_DEFEAT;
    d.title = "Defeat";
    switch(minigame) {
        case MINIGAME_ROCK_FALLING:
            d.messages[0].speaker = rockChar;
            d.messages[0].message = "The boulders may be daunting, but within every stumble lies the chance to ascend.";
            return d;
            break;
        case MINIGAME_PLATFORMER:
            d.messages[0].speaker = horseChar;
            d.messages[0].message = "I'm fast.";
            return d;
            break;
    }
    return d;
}

Dialog wonMiniGameDialog(Minigame minigame) {
    Dialog d;
    d.identifier = DIALOG_MINIGAME_VICTORY;
    d.title = "Victory";
    int finalDialogIndex = 1;
    switch(minigame) {
        case MINIGAME_ROCK_FALLING:
            d.messages[0].speaker = rockChar;
            d.messages[0].message = "Dust settles, you've conquered my rocky climb. The key is yours, a modest win.";
            d.messages[1].speaker = rockChar;
            d.messages[1].message = "Brace for steeper ascents; greater challenges loom ahead. This victory, a foothold on the precipice.";
            d.messages[2].speaker = rockChar;
            d.messages[2].message = "The stones call me elsewhere; my departure is carved in the very essence of this rugged terrain.";
            finalDialogIndex = 3;
            break;
        case MINIGAME_PLATFORMER:
            d.messages[0].speaker = horseChar;
            d.messages[0].message = "Alas, it seems there's a contender who, by some misfortune, managed to outpace my unparalleled swiftness. A humbling revelation, indeed.";
            d.messages[1].speaker = horseChar;
            d.messages[1].message = "Perhaps this is finally my time to go. I must be ashamed of my descent of skill.";
            finalDialogIndex = 2;
            break;
        case MINIGAME_CIPHER:
            d.messages[0].speaker = cipherChar;
            d.messages[0].message = "You are one smart creature, traveller.";
            d.messages[1].speaker = cipherChar;
            d.messages[1].message = "Here is the promised key.";
            d.messages[2].speaker = cipherChar;
            d.messages[2].message = "You may now proceed with your journey, traveller. Perhaps it is an honour since tourism is not what this place is known for.";
            d.messages[3].speaker = cipherChar;
            d.messages[3].message = "Goodbye, I shall now go.";

            finalDialogIndex = 4;
    }

    d.messages[finalDialogIndex].speaker = emptyChar;
    d.messages[finalDialogIndex].message = setKeysDialogTx();
    return d;
}

Dialog playerCipherGoBackDialog() {
    Dialog d;
    d.identifier = DIALOG_CIPHER_GOBACK;
    if (puzzleCipherCompleted && vigenereCipherCompleted && brailleCipherCompleted) {
        d.messages[0].speaker = playerChar;
        d.messages[0].message = "This is new.";
        d.messages[1].speaker = playerChar;
        d.messages[1].message = "Time to jump in.";

    } else {
        d.messages[0].speaker = playerChar;
        d.messages[0].message = "It's too dark down there...";
        d.messages[1].speaker = playerChar;
        d.messages[1].message = "I wonder what these stairs are for.";
        d.messages[2].speaker = playerChar;
        d.messages[2].message = "I think I should try walking in-";
        d.messages[3].speaker = playerChar;
        d.messages[3].message = "...";
        d.messages[4].speaker = playerChar;
        d.messages[4].message = "...nevermind.";
    }

    return d;
}