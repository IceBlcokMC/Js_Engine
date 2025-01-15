/// <reference path="../index.d.ts"/>

/** 玩家 */
declare class Player extends Mob {
    toString(): "<Player>" | string;

    /** 获取玩家的UUID */
    getUniqueId(): string;

    /** 获取玩家的XUID */
    getXuid(): string;

    /** 获取客户端连接地址 */
    getAddress(): {
        /** 地址 */
        host: string;
        /** 端口 */
        port: number;
    };

    /** 发生音符盒消息 */
    sendPopup(
        /** 消息 */
        message: string
    ): void;

    /** 发送提示消息 */
    sendTip(
        /** 消息 */
        message: string
    ): void;

    /** 发送弹幕消息 */
    sendToast(
        /** 标题 */
        title: string,
        /** 内容 */
        content: string
    ): void;

    /** 踢出玩家 */
    kick(
        /** 踢出原因 */
        message: string
    ): void;

    /** 给予玩家经验值 */
    giveExp(
        /** 经验值 */
        amount: number
    ): void;

    /** 给予玩家经验等级 */
    giveExpLevels(
        /** 经验等级 */
        amount: number
    ): void;

    /** 获取经验值进度 */
    getExpProgress(): number;

    /** 设置经验值进度 */
    setExpProgress(progress: number): void;

    /** 获取经验等级 */
    getExpLevel(): number;

    /** 设置经验等级 */
    setExpLevel(level: number): void;

    /** 获取总经验值 */
    getTotalExp(): number;

    /** 玩家是否可以飞行 */
    getAllowFlight(): boolean;

    /** 设置玩家是否可以飞行 */
    setAllowFlight(flight: boolean): void;

    /** 玩家是否在飞行 */
    isFlying(): boolean;

    /** 设置玩家是否在飞行 */
    setFlying(value: boolean): void;

    /** 获取玩家飞行速度 */
    getFlySpeed(): number;

    /** 设置玩家飞行速度 */
    setFlySpeed(value: number): void;

    /** 获取玩家行走速度 */
    getWalkSpeed(): number;

    /** 设置玩家行走速度 */
    setWalkSpeed(value: number): void;

    //getScoreboard():Scoreboard; //TODO Scoreboard

    //setScoreboard(scordboard:Scoreboard):void;//TODO Scoreboard

    /** 发送屏幕消息 */
    sendTitle(
        /** 标题 */
        title: string,
        /** 副标题 */
        subtitle: string
    ): void;

    /** 发送屏幕消息 */
    sendTitle(
        /** 标题 */
        title: string,
        /** 副标题 */
        subtitle: string,
        /** 淡入时间 */
        fade_in: number,
        /** 停留时间 */
        stay: number,
        /** 淡出时间 */
        fade_out: number
    ): void;

    /** 清除屏幕消息 */
    resetTitle(): void;

    //spawnParticle(name:string,location:Location); //TODO Location

    // spawnParticle(name: string, x: number, y: number, z: number): void;

    // spawnParticle(name: string, x: number, y: number, z: number, molang_variables_json?: string): void;

    /** 获取玩家延迟 */
    getPing(): number;

    /** 更新玩家命令补全 */
    updateCommands(): void;

    /** 使玩家执行命令 */
    performCommand(command: string): boolean;

    /** 获取玩家游戏模式 */
    getGameMode(): Enums.GameMode;

    /** 设置玩家游戏模式 */
    setGameMode(
        /** 游戏模式 */
        mode: Enums.GameMode
    ): void;

    //getInventory():PlayerInventory; //TODO PlayerInventory

    /** 获取玩家语言 */
    getLocale(): string;

    /** 获取玩家设备的操作系统 */
    getDeviceOS(): string;

    /** 玩家获取设备ID */
    getDeviceId(): string;

    /** 获取玩家游戏版本 */
    getGameVersion(): string;

    //getSkin():Skin; //TODO Skin

    /** 将玩家转移到另一个服务器 */
    transfer(
        /** 服务器主机 */
        host: string,
        /** 服务器端口 */
        port: number
    ): void;

    //sendForm(form:FormVariant); //TODO FormVariant

    // closeForm(): void;

    //sendPacket(packet:Packet); //TODO Packet
}