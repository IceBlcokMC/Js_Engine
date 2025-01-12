/// <reference path="../index.d.ts"/>

declare class Language{
    translate(text:string):string;

    translate(text:string,locale:string):string;

    translate(text:string,params:string[]):string;

    translate(text:string,params:string[],locale:string):string;
    
    translate(translatable:Translatable):string;

    translate(translatable:Translatable,locale:string):string;

    getLocale():string
}