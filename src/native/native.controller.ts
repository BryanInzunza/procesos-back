import { Controller, Get, Param, ParseIntPipe, Post, Body } from '@nestjs/common';
import { NativeService } from './native.service';

@Controller('native')
export class NativeController {
  constructor(private readonly nativeService: NativeService) {}

  @Get('start-loops')
  startLoops(): { message: string } {
    const message = this.nativeService.startLoops();
    return { message };
  }

  @Get('iteration/:loopNumber')
  getIteration(@Param('loopNumber', ParseIntPipe) loopNumber: number): {
    iteration: number;
    threadId: string;
    pid: number;
  } {
    return this.nativeService.getIteration(loopNumber);
  }

  @Get('pids')
  getPIDs(): number[] {
    return this.nativeService.getPIDs();
  }

  @Post('pause-loop')
  pauseLoop(@Body() body: { loopNumber: number; pause: boolean }): { message: string } {
    const { loopNumber, pause } = body;
    const message = this.nativeService.pauseLoop(loopNumber, pause);
    return { message };
  }
}