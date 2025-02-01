import { Injectable } from '@nestjs/common';
const addon = require('../../build/Release/addon');

@Injectable()
export class NativeService {
  startLoops(): string {
    return addon.startLoops();
  }

  getIteration(loopNumber: number): { iteration: number, threadId: string, pid: number } {
    const result = addon.getIteration(loopNumber);
    return {
      iteration: result.iteration,
      threadId: result.threadId,
      pid: result.pid,
    };
  }

  getPIDs(): number[] {
    return addon.getPIDs();
  }
}