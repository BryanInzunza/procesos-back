import { Injectable } from '@nestjs/common';
const addon = require('../../build/Release/addon.node');

@Injectable()
export class NativeService {
  startLoops(): string {
    return addon.startLoops();
  }

  getIteration(loopNumber: number): string {
    return addon.getIteration(loopNumber);
  }

  getPIDs(): number[] {
    return addon.getPIDs();
  }
}