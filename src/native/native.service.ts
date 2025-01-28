import { Injectable } from '@nestjs/common';
const addon = require('../../build/Release/addon');

@Injectable()
export class NativeService {
    startLoops(): string {
        return addon.startLoops();
    }

    getIteration(loopNumber: number): string {
        return addon.getIteration(loopNumber);
    }
}